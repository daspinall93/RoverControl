/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include "LocomModule.h"
#include "Utils.h"

/* INCLUDE ENUMERATIONS */
#include "mavlink/v2.0/SoteriaRover/mavlink.h"

LocomModule::LocomModule(MotorModule* p_M1, MotorModule* p_M2)
{
    /* ASSIGN POINTERS TO THE MOTORS FOR SENDING COMMANDS */
    p_Motor1 = *p_M1;
    p_Motor2 = *p_M2;

    /* INITIALISE ALL DATA TO 0 */
    memset(&Report, 0, sizeof(Report));
    memset(&Command, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Config));
    memset(&State, 0, sizeof(State));

}
void LocomModule::Start()
{

    /* INITIALISE THE STATE STRUCTURE */
    State.mode = LOCOM_MODE_STOP;
    State.modeElapsedTime = 0;
    State.modeStartTime = 0;
}

void LocomModule::Execute()
{
    Debug();

    /* CHECK IF NEW COMMAND HAS BEEN ISSUED */
    if (Command.newCommand)
    {
	/* SWITCH ON THE COMMAND ID */
	switch(Command.commandid)
	{
	    case LOCOM_COMMAND_STOP:

		ModeStop();
		break;

	    case LOCOM_COMMAND_STRAIGHT_FORWARD:

		ModeStraightForward();
		break;

	    case LOCOM_COMMAND_STRAIGHT_BACKWARD:

		ModeStraightBackward();
		break;

	    case LOCOM_COMMAND_TURN_LEFT:

		ModeTurnLeft();
		break;

	    case LOCOM_COMMAND_TURN_RIGHT:

		ModeTurnRight();
		break;

	    default:

		break;

	}

	/* INITALISE THE TIMER FOR THE COMMAND */
	State.modeStartTime = utils_getTimems();
	State.modeElapsedTime = 0;
	Command.newCommand = 0;

    }
    else
    {

	/* CHECK IF THE COMMAND HAS FINISHED */
	State.modeElapsedTime = (utils_getTimems() - State.modeStartTime);
	if(State.modeElapsedTime >= Command.durmsec)
	{
	    /* RESET TIMER AND SET MODE TO STOP */
	    State.modeStartTime = utils_getTimems();;
	    State.modeElapsedTime = 0;
	    ModeStop();

	}

    }
    //execute the changes for the motors
    Debug();
}

/* MODE FUNCTIONS WITH CORRESPONDING DIRECTION COMMANDS TO MOTORS */

void LocomModule::ModeStop()
{

    p_Motor1->Command.commandid = MOTOR_COMMAND_STOP;
    p_Motor1->Command.newCommand = 1;
    p_Motor1->Command.power = Command.power;

    p_Motor2->Command.commandid = MOTOR_COMMAND_STOP;
    p_Motor2->Command.newCommand = 1;
    p_Motor2->Command.power = Command.power;

    State.mode = LOCOM_MODE_STOP;
}

void LocomModule::ModeStraightForward()
{
    p_Motor1->Command.commandid = MOTOR_COMMAND_FORWARD;
    p_Motor1->Command.newCommand = 1;
    p_Motor1->Command.power = Command.power;

    p_Motor2->Command.commandid = MOTOR_COMMAND_FORWARD;
    p_Motor2->Command.newCommand = 1;
    p_Motor2->Command.power = Command.power;

    State.mode = LOCOM_MODE_STRAIGHT_FORWARD;
}

void LocomModule::ModeStraightBackward()
{
    p_Motor1->Command.commandid = MOTOR_COMMAND_BACKWARD;
    p_Motor1->Command.newCommand = 1;
    p_Motor1->Command.power = Command.power;
    p_Motor1->Execute();

    p_Motor2->Command.commandid = MOTOR_COMMAND_BACKWARD;
    p_Motor2->Command.newCommand = 1;
    p_Motor2->Command.power = Command.power;
    p_Motor2->Execute();

    State.mode = LOCOM_MODE_STRAIGHT_BACKWARD;
}

void LocomModule::ModeTurnRight()
{
    p_Motor1->Command.commandid = MOTOR_COMMAND_FORWARD;
    p_Motor1->Command.newCommand = 1;
    p_Motor1->Command.power = Command.power;

    p_Motor2->Command.commandid = MOTOR_COMMAND_BACKWARD;
    p_Motor2->Command.newCommand = 1;
    p_Motor2->Command.power = Command.power;

    State.mode = LOCOM_MODE_TURN_RIGHT;
}

void LocomModule::ModeTurnLeft()
{
    p_Motor1->Command.commandid = MOTOR_COMMAND_BACKWARD;
    p_Motor1->Command.newCommand = 1;
    p_Motor1->Command.power = Command.power;

    p_Motor2->Command.commandid = MOTOR_COMMAND_FORWARD;
    p_Motor2->Command.newCommand = 1;
    p_Motor2->Command.power = Command.power;

    State.mode = LOCOM_MODE_TURN_LEFT;
}

void LocomModule::UpdateReport()
{
    Report.mode = State.mode;
    Report.modeElapsedTime = State.modeElapsedTime;
}

void LocomModule::Debug()
{
    printf("[LOCOM]Mode = %d \t T elapsed = %ld \n", State.mode, State.modeElapsedTime);
}



