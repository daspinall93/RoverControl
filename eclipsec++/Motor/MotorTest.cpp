/*
 * MotorTest.cpp
 *
 *  Created on: 23 Feb 2018
 *      Author: dan
 */

#include "MotorModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"


int main()
{

	MotorModule Motor = MotorModule();
	mavlink_motor_command_t MotorCommand;
	mavlink_motor_report_t MotorReport;

	Motor.Start();

	MotorCommand.newCommand = 1;
	MotorCommand.commandid = MOTOR_COMMAND_STRAIGHT_FORWARD;
	MotorCommand.power_per = 50;
	MotorCommand.duration_ms = 1000000;

	Motor.Execute(&MotorCommand, &MotorReport);

	MotorCommand.newCommand = 1;
	MotorCommand.commandid = MOTOR_COMMAND_TURN_LEFT;
	MotorCommand.power_per = 20;
	MotorCommand.duration_ms = 1000000;

	Motor.Execute(&MotorCommand, &MotorReport);

	return 0;
}
