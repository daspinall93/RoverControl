/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include "LocomModule.h"
#include "../Utils/Utils.h"

void LocomModule::Start()
{

	/* INITIALISE THE STATE STRUCTURE */
	mode = LOCOM_MODE_STOP;
	modeElapsedTime_ms = 0;
	modeStartTime_ms = 0;
}

void LocomModule::Execute(mavlink_locom_report_t* p_LocomReport_out,
		mavlink_locom_command_t* p_LocomCommand_in,
		mavlink_motor_command_t* p_MotorCommand_out)
{
	//Debug();

	/* CHECK IF NEW COMMAND HAS BEEN ISSUED */
	if (p_LocomCommand_in->newCommand)
	{
		/* SWITCH ON THE COMMAND ID */
		switch (p_LocomCommand_in->commandid)
		{
		case LOCOM_COMMAND_STOP:

			ModeStop(p_MotorCommand_out, p_LocomCommand_in);
			break;

		case LOCOM_COMMAND_STRAIGHT_FORWARD:

			ModeStraightForward(p_MotorCommand_out, p_LocomCommand_in);
			break;

		case LOCOM_COMMAND_STRAIGHT_BACKWARD:

			ModeStraightBackward(p_MotorCommand_out, p_LocomCommand_in);
			break;

		case LOCOM_COMMAND_TURN_LEFT:

			ModeTurnLeft(p_MotorCommand_out, p_LocomCommand_in);
			break;

		case LOCOM_COMMAND_TURN_RIGHT:

			ModeTurnRight(p_MotorCommand_out, p_LocomCommand_in);
			break;

		default:

			break;

		}

		/* INITALISE THE TIMER FOR THE COMMAND */
		modeStartTime_ms = Utils::GetTimems();
		modeElapsedTime_ms = 0;
		p_LocomCommand_in->newCommand = 0;

	}
	else
	{

		/* UPDATE ELAPSED TIME */
		modeElapsedTime_ms = (Utils::GetTimems() - modeStartTime_ms);

		/* CHECK IF THE COMMAND HAS FINISHED */
		if (modeElapsedTime_ms >= p_LocomCommand_in->duration_ms)
		{
			/* RESET TIMER AND SET MODE TO STOP */
			modeStartTime_ms = Utils::GetTimems();
			modeElapsedTime_ms = 0;
			ModeStop(p_MotorCommand_out, p_LocomCommand_in);

		}

	}
	//execute the changes for the motors
	Debug();
}

void LocomModule::ModeStop(mavlink_motor_command_t* p_MotorCommand_out,
		const mavlink_locom_command_t* p_LocomCommand_in)
{

	p_MotorCommand_out->m1_commandid = MOTOR_COMMAND_STOP;
	p_MotorCommand_out->m1_newCommand = 1;
	p_MotorCommand_out->m1_power_per = p_LocomCommand_in->power_per;

	p_MotorCommand_out->m2_commandid = MOTOR_COMMAND_STOP;
	p_MotorCommand_out->m2_newCommand = 1;
	p_MotorCommand_out->m2_power_per = p_LocomCommand_in->power_per;

	mode = LOCOM_MODE_STOP;
}

void LocomModule::ModeStraightForward(
		mavlink_motor_command_t* p_MotorCommand_out,
		const mavlink_locom_command_t* p_LocomCommand_in)
{

	p_MotorCommand_out->m1_commandid = MOTOR_COMMAND_FORWARD;
	p_MotorCommand_out->m1_newCommand = 1;
	p_MotorCommand_out->m1_power_per = p_LocomCommand_in->power_per;

	p_MotorCommand_out->m2_commandid = MOTOR_COMMAND_FORWARD;
	p_MotorCommand_out->m2_newCommand = 1;
	p_MotorCommand_out->m2_power_per = p_LocomCommand_in->power_per;

	mode = LOCOM_MODE_STRAIGHT_FORWARD;
}

void LocomModule::ModeStraightBackward(
		mavlink_motor_command_t* p_MotorCommand_out,
		const mavlink_locom_command_t* p_LocomCommand_in)
{

	p_MotorCommand_out->m1_commandid = MOTOR_COMMAND_BACKWARD;
	p_MotorCommand_out->m1_newCommand = 1;
	p_MotorCommand_out->m1_power_per = p_LocomCommand_in->power_per;

	p_MotorCommand_out->m2_commandid = MOTOR_COMMAND_BACKWARD;
	p_MotorCommand_out->m2_newCommand = 1;
	p_MotorCommand_out->m2_power_per = p_LocomCommand_in->power_per;

	mode = LOCOM_MODE_STRAIGHT_BACKWARD;
}

void LocomModule::ModeTurnRight(mavlink_motor_command_t* p_MotorCommand_out,
		const mavlink_locom_command_t* p_LocomCommand_in)
{

	p_MotorCommand_out->m1_commandid = MOTOR_COMMAND_FORWARD;
	p_MotorCommand_out->m1_newCommand = 1;
	p_MotorCommand_out->m1_power_per = p_LocomCommand_in->power_per;

	p_MotorCommand_out->m2_commandid = MOTOR_COMMAND_BACKWARD;
	p_MotorCommand_out->m2_newCommand = 1;
	p_MotorCommand_out->m2_power_per = p_LocomCommand_in->power_per;

	mode = LOCOM_MODE_TURN_RIGHT;
}

void LocomModule::ModeTurnLeft(mavlink_motor_command_t* p_MotorCommand_out,
		const mavlink_locom_command_t* p_LocomCommand_in)
{

	p_MotorCommand_out->m1_commandid = MOTOR_COMMAND_BACKWARD;
	p_MotorCommand_out->m1_newCommand = 1;
	p_MotorCommand_out->m1_power_per = p_LocomCommand_in->power_per;

	p_MotorCommand_out->m2_commandid = MOTOR_COMMAND_FORWARD;
	p_MotorCommand_out->m2_newCommand = 1;
	p_MotorCommand_out->m2_power_per = p_LocomCommand_in->power_per;

	mode = LOCOM_MODE_TURN_LEFT;
}

void LocomModule::UpdateReport(mavlink_locom_report_t* p_LocomReport_out)
{

	p_LocomReport_out->mode = mode;
	p_LocomReport_out->modeElapsedTime_ms = modeElapsedTime_ms;
}

void LocomModule::Debug()
{
	printf("[LOCOM]Mode = %d \t Time elapsed = %ld \n", mode,
			modeElapsedTime_ms);

}

