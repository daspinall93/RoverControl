/*
 * TelecModule.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */

#include "TelecModule.h"

#include <iostream>

void TelecModule::Start()
{

}

void TelecModule::Execute(mavlink_telec_report_t* p_TelecReport_out,
		mavlink_comms_report_t* p_CommsReport_in)
{
	/* AS ONLY ACCEPTING ONE TC ON EACH PASS ENSURE THE MESSAGE BUFFER IS EMPTY */
	memset(parsedMsgs, 0, MSG_BUFFER_SIZE);
	numParsedMsgs = 0;

	/* HANDLE TC FIRST OF ALL */
	/* CHECK IF A NEW DATA FROM GS HAS ARRIVED */
	std::cout << "[TELEC]Number of bytes received = " << p_CommsReport_in->numBytesRec << std::endl;
	if (p_CommsReport_in->numBytesRec > 0)
	{
		ParseMessages(p_CommsReport_in);

	}
	else
	{
		memset(parsedMsgs, 0, MSG_BUFFER_SIZE);
		numParsedMsgs = 0;
	}

	/* UPDATE REPORT TO INCLUDE THE NEW TC */
	UpdateReport(p_TelecReport_out);


	/* CALL DEBUG TO SEE STATUS OF THE MODULE */
	Debug();
}

void TelecModule::ParseMessages(const mavlink_comms_report_t* p_CommsReport_in)
{
	numParsedMsgs = 0;
	uint16_t byteNum = 0;

	/* CYCLE THROUGH EVERY BYTE IN THE BUFFER AND PARSE FIRST MESSAGE*/
	/* NOTE: currently only parsing one message due to segmentation fault */
	while (mavlink_parse_char(MAVLINK_COMM_0,
			p_CommsReport_in->msgRecBuffer[byteNum], parsedMsgs, &mavlinkStatus)
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
		p_TelecReport_out->msgid = parsedMsgs[0].msgid;

		/* LOOP THROUGH EVERY COMMAND CURRENTLY IN PARSED MESSAGES */
		switch (parsedMsgs[0].msgid)
		{
		case MAVLINK_MSG_ID_MOTOR_COMMAND:
			p_TelecReport_out->MotorCommand.commandid =
					mavlink_msg_motor_command_get_commandid(&parsedMsgs[0]);
			p_TelecReport_out->MotorCommand.duration_ms =
					mavlink_msg_motor_command_get_duration_ms(&parsedMsgs[0]);
			p_TelecReport_out->MotorCommand.power_per =
					mavlink_msg_motor_command_get_power_per(&parsedMsgs[0]);
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
