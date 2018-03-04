/*
 * LocomTest.cpp
 *
 *  Created on: 22 Feb 2018
 *      Author: dan
 */

#include "LocomModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include <stdio.h>
#include <unistd.h>

void mavlink_locom_command_set(mavlink_locom_command_t* packet,
		uint8_t commandid, uint64_t duration_ms, uint32_t power_per,
		uint8_t newCommand);

void mavlink_motor_command_print(mavlink_motor_command_t* p_MotorCommand);

int main()
{

	LocomModule Locom = LocomModule();
	mavlink_locom_command_t LocomCommand;
	mavlink_motor_command_t MotorCommand;
	mavlink_locom_report_t LocomReport;

	Locom.Start();

	/* SIMULATE WHAT THE COMMS SECTION WOULD DO */
	mavlink_locom_command_set(&LocomCommand, LOCOM_COMMAND_STRAIGHT_FORWARD,
			6000, 50, 1);

	Locom.Execute(&LocomReport, &LocomCommand, &MotorCommand);
	mavlink_motor_command_print(&MotorCommand);

	fflush(stdout);
	sleep(5);

	Locom.Execute(&LocomReport, &LocomCommand, &MotorCommand);
	mavlink_motor_command_print(&MotorCommand);

	mavlink_locom_command_set(&LocomCommand, LOCOM_COMMAND_TURN_LEFT, 4000, 30,
			1);

	Locom.Execute(&LocomReport, &LocomCommand, &MotorCommand);
	mavlink_motor_command_print(&MotorCommand);

	fflush(stdout);
	sleep(5);

	Locom.Execute(&LocomReport, &LocomCommand, &MotorCommand);
	mavlink_motor_command_print(&MotorCommand);

	return 0;

}

void mavlink_locom_command_set(mavlink_locom_command_t* packet,
		uint8_t commandid, uint64_t duration_ms, uint32_t power_per,
		uint8_t newCommand)
{

	packet->duration_ms = duration_ms;
	packet->power_per = power_per;
	packet->commandid = commandid;
	packet->newCommand = newCommand;

}

void mavlink_motor_command_print(mavlink_motor_command_t* p_MotorCommand)
{
	printf("[MOTOR1]command = %d \t power_per = %d \t newCommand = %d \n",
			p_MotorCommand->m1_commandid, p_MotorCommand->m1_power_per,
			p_MotorCommand->m1_newCommand);
	printf("[MOTOR2]command = %d \t power_per = %d \t newCommand = %d \n",
			p_MotorCommand->m2_commandid, p_MotorCommand->m2_power_per,
			p_MotorCommand->m2_newCommand);
}
