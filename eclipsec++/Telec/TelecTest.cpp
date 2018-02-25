/*
 * tmtcTest.cpp
 *
 *  Created on: 25 Feb 2018
 *      Author: dan
 */

#include "../Comms/CommsModule.h"
#include <unistd.h>

#include "TelecInterfaceStructs.h"
#include "TelecModule.h"

#include <stdio.h>

void printTelecReport(mavlink_telec_report_t* p_TelecReport);

int main()
{
	TelecModule Telec = TelecModule();
	mavlink_telec_report_t TelecReport;
	mavlink_comms_report_t CommsReport;
	mavlink_message_t msg;

	memset(CommsReport.msgRecBuffer, 0, 2041);

	/* SIMULATE A RECEIVED TC FROM COMMS MODULE */
	mavlink_msg_locom_command_pack(1, 1, &msg, LOCOM_COMMAND_TURN_LEFT, 3000,
			50, 1);
	CommsReport.numBytesRec = mavlink_msg_to_send_buffer(
			CommsReport.msgRecBuffer, &msg);

	Telec.Start();

	Telec.Execute(&TelecReport, &CommsReport);

	printTelecReport(&TelecReport);

	/* SIMULATE NO MESSAGE BEING RECEIVED FROM THE */
	memset(CommsReport.msgRecBuffer, 0, 2041);
	CommsReport.numBytesRec = 0;

	Telec.Execute(&TelecReport, &CommsReport);

	/* SIMULATE ANOTHER MESSAGE BEING RECEIVED */
	mavlink_msg_motor_command_pack(1, 1, &msg, MOTOR_COMMAND_FORWARD, 1, 40, MOTOR_COMMAND_STOP, 1, 0);
	CommsReport.numBytesRec = mavlink_msg_to_send_buffer(
			CommsReport.msgRecBuffer, &msg);

	Telec.Start();

	Telec.Execute(&TelecReport, &CommsReport);

	printTelecReport(&TelecReport);

	return 0;
}

void printTelecReport(mavlink_telec_report_t* p_TelecReport)
{
	if (p_TelecReport->newTc)
	{
		/* SEE WHAT THE COMMAND IS */
		switch (p_TelecReport->msgid)
		{
		case MAVLINK_MSG_ID_LOCOM_COMMAND:
			printf("id = %d, dur = %ld, power = %d, newCom = %d \n", p_TelecReport->LocomCommand.commandid,
					p_TelecReport->LocomCommand.duration_ms,
					p_TelecReport->LocomCommand.power_per,
					p_TelecReport->LocomCommand.newCommand);

			break;

		case MAVLINK_MSG_ID_MOTOR_COMMAND:
			printf("id = %d, newCom = %d power = %d \n", p_TelecReport->MotorCommand.m1_commandid,
					p_TelecReport->MotorCommand.m1_newCommand,
					p_TelecReport->MotorCommand.m1_power_per);
			printf("id = %d, newCom = %d power = %d \n", p_TelecReport->MotorCommand.m2_commandid,
					p_TelecReport->MotorCommand.m2_newCommand,
					p_TelecReport->MotorCommand.m2_power_per);

			break;

		}
	}
}
