/*
 * main.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include <stdio.h>
#include <unistd.h>

#include "LocomClass.h"
#include "Utils.h"

int main(){

	LocomClass Locom;
	Locom.Parameters.pwmResolution = 1024;
	Locom.Start();

	Locom.Command.commandid = LOCOM_COMMAND_STRAIGHT_FORWARD;
	Locom.Command.newCommand = true;
	Locom.Command.durmsec = 5000;
	Locom.Command.power = 50;

	//every 0.1s execute locomotion object
	Locom.Execute();

	//execute motor control at 0.01s (incase some form of feedback is implemented)
	Locom.Motor1.Execute();
	Locom.Motor2.Execute();


	fflush(stdout);
	sleep(2);

	Locom.Command.commandid = LOCOM_COMMAND_STOP;
	Locom.Command.newCommand = true;
	Locom.Command.durmsec = 5000;
	Locom.Command.power = 50;

	Locom.Execute();

	Locom.Motor1.Execute();
	Locom.Motor2.Execute();

	return 1;

}
