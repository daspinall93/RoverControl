/*
 * MotorTest.cpp
 *
 *  Created on: 23 Feb 2018
 *      Author: dan
 */

#include "MotorModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"

void mavlink_msg_motor_command_set(mavlink_motor_command_t* packet,
		uint8_t m1_commandid, uint8_t m1_newCommand, uint32_t m1_power_per,
		uint8_t m2_commandid, uint8_t m2_newCommand, uint32_t m2_power_per);

int main()
{

	MotorModule Motor = MotorModule();
	mavlink_motor_command_t MotorCommand;
	mavlink_motor_report_t MotorReport;

	Motor.Start();

	mavlink_msg_motor_command_set(&MotorCommand, MOTOR_COMMAND_FORWARD, 1, 50,
			MOTOR_COMMAND_FORWARD, 1, 50);

	Motor.Execute(&MotorCommand, &MotorReport);

	mavlink_msg_motor_command_set(&MotorCommand, MOTOR_COMMAND_BACKWARD, 1, 20,
			MOTOR_COMMAND_FORWARD, 1, 70);

	Motor.Execute(&MotorCommand, &MotorReport);

	mavlink_msg_motor_command_set(&MotorCommand, MOTOR_COMMAND_STOP, 1, 0,
			MOTOR_COMMAND_FORWARD, 1, 70);

	Motor.Execute(&MotorCommand, &MotorReport);

	return 0;
}

void mavlink_msg_motor_command_set(mavlink_motor_command_t* packet,
		uint8_t m1_commandid, uint8_t m1_newCommand, uint32_t m1_power_per,
		uint8_t m2_commandid, uint8_t m2_newCommand, uint32_t m2_power_per)
{
	packet->m1_power_per = m1_power_per;
	packet->m1_commandid = m1_commandid;
	packet->m1_newCommand = m1_newCommand;

	packet->m2_power_per = m2_power_per;
	packet->m2_commandid = m2_commandid;
	packet->m2_newCommand = m2_newCommand;

}

