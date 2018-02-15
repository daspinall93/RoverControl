/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */
#include "LocomModule.h"

/* PUBLIC FUNCTIONS */

/*
 * Function to start/setup the object by configuring the motors
 */

void LocomModule::Start(MotorModule* M1, MotorModule* M2)
{
	//use the motor modules created outside of the locom module to send commands
	Motor1 = *M1;
	Motor2 = *M2;

	//initialise the state structure
	State.mode = LOCOM_MODE_STOP;
	State.modeElapsedTime = 0;
	State.modeStartTime = 0;
}

void LocomModule::Execute()
{
	Debug();

	//execute mode transitions for locom
	if (Command.newCommand)
	{
		switch(Command.commandid)
		{
			case LOCOM_COMMAND_STOP:
				//stay in standby

				ModeStop();
				break;

			case LOCOM_COMMAND_STRAIGHT_FORWARD:
				//drive straight command

				ModeStraightForward();
				break;

			case LOCOM_COMMAND_STRAIGHT_BACKWARD:
				//go in a straight line backwards

				//set to drive all wheels backward
				ModeStraightBackward();
				break;

			case LOCOM_COMMAND_TURN_LEFT:
				//turn left command

				//set to drive left wheels back and right forward
				ModeTurnLeft();
				break;

			case LOCOM_COMMAND_TURN_RIGHT:
				//turn right command

				//set to drive left wheels forward and right backward
				ModeTurnRight();
				break;

			default:
				//invalid command

				break;

		}

		//set the time at which the command started
		State.modeStartTime = utils_getTimems();
		State.modeElapsedTime = 0;
		Command.newCommand = 0;	//set to 0 as new command has been processed

	}
	else
	{

		//no new command so need to check time elapsed
		State.modeElapsedTime = (utils_getTimems() - State.modeStartTime);
		if(State.modeElapsedTime >= Command.durmsec)
		{
			//the command has ended so turn of motors and reset elapsed time

			State.modeStartTime = utils_getTimems();;
			State.modeElapsedTime = 0;
			ModeStop();

		}

	}

	//execute the changes for the motors
	Debug();
}

/*
 * Private function to put the rover into the stop mode
 */
void LocomModule::ModeStop()
{
	//currenty only need to set directions as not using PWM
	Motor1.Command.commandid = MOTOR_COMMAND_STOP;
	Motor1.Command.newCommand = 1;
	Motor1.Command.power = Command.power;

	Motor2.Command.commandid = MOTOR_COMMAND_STOP;
	Motor2.Command.newCommand = 1;
	Motor2.Command.power = Command.power;

	//update to the new state
	State.mode = LOCOM_MODE_STOP;
}

/*
 * Private function to put the rover into the drive straight forward mode
 */
void LocomModule::ModeStraightForward()
{
	Motor1.Command.commandid = MOTOR_COMMAND_FORWARD;
	Motor1.Command.newCommand = 1;
	Motor1.Command.power = Command.power;

	Motor2.Command.commandid = MOTOR_COMMAND_FORWARD;
	Motor2.Command.newCommand = 1;
	Motor2.Command.power = Command.power;

	//update to the new state
	State.mode = LOCOM_MODE_STRAIGHT_FORWARD;
}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomModule::ModeStraightBackward()
{
	Motor1.Command.commandid = MOTOR_COMMAND_BACKWARD;
	Motor1.Command.newCommand = 1;
	Motor1.Command.power = Command.power;
	Motor1.Execute();

	Motor2.Command.commandid = MOTOR_COMMAND_BACKWARD;
	Motor2.Command.newCommand = 1;
	Motor2.Command.power = Command.power;
	Motor2.Execute();

	//update to the new state
	State.mode = LOCOM_MODE_STRAIGHT_FORWARD;
}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomModule::ModeTurnRight()
{
	Motor1.Command.commandid = MOTOR_COMMAND_FORWARD;
	Motor1.Command.newCommand = 1;
	Motor1.Command.power = Command.power;

	Motor2.Command.commandid = MOTOR_COMMAND_BACKWARD;
	Motor2.Command.newCommand = 1;
	Motor2.Command.power = Command.power;

	//update to the new state
	State.mode = LOCOM_MODE_TURN_RIGHT;
}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomModule::ModeTurnLeft()
{
	Motor1.Command.commandid = MOTOR_COMMAND_BACKWARD;
	Motor1.Command.newCommand = 1;
	Motor1.Command.power = Command.power;

	Motor2.Command.commandid = MOTOR_COMMAND_FORWARD;
	Motor2.Command.newCommand = 1;
	Motor2.Command.power = Command.power;
	//update to the new state
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



