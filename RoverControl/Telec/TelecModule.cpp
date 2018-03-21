/*
 * TelecModule.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */

#include "TelecModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include <iostream>

void TelecModule::Start()
{
	std::cout << "[TELEC]Telec starting ..." << std::endl;
}

void TelecModule::Execute(mavlink_telec_report_t* p_TelecReport_out,
		mavlink_comms_report_t* p_CommsReport_in)
{
	/* AS ONLY ACCEPTING ONE TC ON EACH PASS ENSURE THE MESSAGE IS EMPTY */
	memset((char*)&parsedMsg, 0, sizeof(parsedMsg));
	numParsedMsgs = 0;

	/* CHECK IF A NEW DATA FROM GS HAS ARRIVED */
	if (p_CommsReport_in->numBytesRec > 0)
	{
		memcpy(buffer, p_CommsReport_in->msgRecBuffer, sizeof(buffer));
		ParseMessages(p_CommsReport_in);

	}

	/* UPDATE REPORT TO INCLUDE THE NEW TC */
	UpdateReport(p_TelecReport_out);

	/* CALL DEBUG TO SEE STATUS OF THE MODULE */
	Debug();
}

void TelecModule::ParseMessages(const mavlink_comms_report_t* p_CommsReport_in)
{
	int byteNum = 0;
	mavlink_status_t mavlinkStatus;

	/* ONLY ACCEPT THE FIRST TC IN THE BUFFER */
	while (mavlink_parse_char(MAVLINK_COMM_0,
			buffer[byteNum], &parsedMsg, &mavlinkStatus)
			!= 1)
	{
		byteNum++;
	}

	numParsedMsgs++;

}

void TelecModule::UpdateReport(mavlink_telec_report_t* p_TelecReport_out)
{
	/* DETERMINE IF NEW TC IS AVAILABLE */
	if (numParsedMsgs > 0)
	{
		p_TelecReport_out->newTc = 1;

		/* SET THE MESSAGE ID SO THAT NEW COMMAND IS KNOWN */
		p_TelecReport_out->msgid = parsedMsg.msgid;

		/* LOOP THROUGH EVERY COMMAND CURRENTLY IN PARSED MESSAGES */
		switch (parsedMsg.msgid)
		{
		case MAVLINK_MSG_ID_MOTOR_COMMAND:
			p_TelecReport_out->MotorCommand.commandid =
					mavlink_msg_motor_command_get_commandid(&parsedMsg);
			p_TelecReport_out->MotorCommand.duration_ms =
					mavlink_msg_motor_command_get_duration_ms(&parsedMsg);
			p_TelecReport_out->MotorCommand.power_per =
					mavlink_msg_motor_command_get_power_per(&parsedMsg);
			p_TelecReport_out->MotorCommand.newCommand = 1;

			break;

		}
	}
	else
	{
		p_TelecReport_out->newTc = 0;
	}


}

void TelecModule::Debug()
{
	std::cout << "[TELEC]Number parsed msg = " << numParsedMsgs << std::endl;
}
