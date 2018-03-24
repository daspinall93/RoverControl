/*
 * TelecModule.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */

/*
 * Take the received buffer from the comms module and produce
 * commands for other modules in the TelecReport.xCommand
 * structure
 */

#include "TelecModule.h"
#include "mavlink.h"
#include <stdint.h>
#include <iostream>

void TelecModule::Start()
{
	std::cout << "[TELEC]Telec starting ..." << std::endl;
}

void TelecModule::Execute(mavlink_telec_report_t& p_TelecReport_out,
		mavlink_telec_command_t& TelecCommand_in)
{
	// Ensure the parsedMsg variable is empty from last pass
	memset((char*) &parsedMsg, 0, sizeof(parsedMsg));
	numParsedMsgs = 0;

	// Ensure the local buffer is empty
	memset(&buffer, 0, sizeof(buffer));
	bufferLength = 0;

	// Copy the Comms report buffer to a local one
	memcpy(buffer, TelecCommand_in.buffer, sizeof(TelecCommand_in.bufferLength));
	bufferLength = TelecCommand_in.bufferLength;

	// Parse the message
	ParseMessages(p_CommsReport_in);

	// Update the report with new commands
	UpdateReport(p_TelecReport_out);

	// Print to screen
	Debug();
}

void TelecModule::ParseMessages(const mavlink_comms_report_t& TelecCommand_in)
{
	// Check if anything has been received
	if (bufferLength > 0)
	{
		int byteNum = 0;

		// Loop through buffer until either a message is parsed or the end of the buffer is reached
		while (byteNum <= bufferLength)
		{
			// Parse has finished in function returns 1
			if (mavlink_parse_char(MAVLINK_COMM_0, buffer[byteNum], &parsedMsg,
					&mavlinkStatus) == 1)
			{
				numParsedMsgs++;
				break;
			}
			byteNum++;

		}

	}

}

void TelecModule::UpdateReport(mavlink_telec_report_t& TelecReport_out)
{
	/* DETERMINE IF NEW TC IS AVAILABLE */
	if (numParsedMsgs > 0)
	{
		// Notify that new command has been received
		p_TelecReport_out.newTc = 1;

		/* SET THE MESSAGE ID SO THAT TYPE OF NEW COMMAND IS KNOWN */
		p_TelecReport_out.msgid = parsedMsg.msgid;

		// Get the command from the parsedMsg and update the report
		switch (parsedMsg.msgid)
		{
		case MAVLINK_MSG_ID_MOTOR_COMMAND:
			p_TelecReport_out.MotorCommand.commandid =
					mavlink_msg_motor_command_get_commandid(&parsedMsg);
			p_TelecReport_out.MotorCommand.duration_ms =
					mavlink_msg_motor_command_get_duration_ms(&parsedMsg);
			p_TelecReport_out.MotorCommand.power_per =
					mavlink_msg_motor_command_get_power_per(&parsedMsg);
			p_TelecReport_out.MotorCommand.newCommand = 1;

			break;

		case MAVLINK_MSG_ID_SONAR_COMMAND:
			p_TelecReport_out.SonarCommand.newCommand =
					mavlink_msg_sonar_command_get_newCommand(&parsedMsg);

			break;

		case MAVLINK_MSG_ID_INERT_COMMAND:
			p_TelecReport_out.InertCommand.newCommand =
					mavlink_msg_inert_command_get_newCommand(&parsedMsg);

			break;

		default:

			break;
		}
	}
	else
	{
		p_TelecReport_out.newTc = 0;
	}

}

void TelecModule::Debug()
{
	std::cout << "[TELEC]Number of parsed messages = " << numParsedMsgs << std::endl;
	if (numParsedMsgs > 0)
	{
		std::cout << "[TELEC]Message ID = " << parsedMsg.msgid << std::endl;
	}
}
