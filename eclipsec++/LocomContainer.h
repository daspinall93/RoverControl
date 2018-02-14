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
#include "MotorContainer.h"

/* all enumerations are define in SoteriaRover header from Mavlink */

#define ENA 18	//PWM
#define ENB 19	//PWM
//M1=right motor
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
//M2 = left motor
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2

class LocomContainer
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

	struct
	{
		//struct containg some configuration parameters for the object
		int pwmResolution;
	} Parameters;

	//public member functions for calling
	LocomContainer(){};	//replace locom_start()
	void Start();
	void Execute();

	//private objects
	MotorClass Motor1;
	MotorClass Motor2;

private:
	//members that can only be accessed by the class

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


protected:

};

#endif /* C___LOCOM_H_ */
