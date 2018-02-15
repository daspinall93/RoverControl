/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

/* TODO
 * -Incorporate ability to control the power being applied to the motors (PWM)
 * -
 */
#ifndef C___LOCOM_H_
#define C___LOCOM_H_

#include <stdio.h>
#include <stdint.h>

#include "Utils.h"
#include "mavlink/v2.0/SoteriaRover/mavlink.h"
#include "MotorModule.h"

/* all enumerations are define in SoteriaRover header from Mavlink */


class LocomModule
{
public:
	//members that can be accessed from outside of the class

	//public data members for reading and setting appropriately
	struct
	{
		//struct containing the status report to be seen externally
		long int modeElapsedTime;
		uint8_t mode;	//a valid submode using LOCOM_STATE_x
	} Report;

	struct
	{
		//struct containing the command for locom object to execute
		int power;	//power (0 to 100%)
		int durmsec;	//duration in msec
		uint8_t commandid;	//command using valid LOCOM_COMMAND_x
		bool newCommand;	//boolean for if a new command has been produced
	} Command;

	LocomModule(){};	//replace locom_start()

	//members that can only be accessed by the class
	struct
	{
		//struct containg some configuration parameters for the object

	} Config;

	//public member functions for calling

	void Start(MotorModule* M1, MotorModule* M2);
	void Execute();

	//private objects
	MotorModule Motor1;
	MotorModule Motor2;
	struct
	{
		//struct containing to keep track of internal state of the object
		long int modeStartTime;
		long int modeElapsedTime;
		uint8_t mode;
	} State;

	//private member functions called internally
	//mode actions
	void ModeStop();
	void ModeStraightForward();
	void ModeStraightBackward();
	void ModeTurnRight();
	void ModeTurnLeft();

	void UpdateReport();
	void Debug();

};

#endif /* C___LOCOM_H_ */
