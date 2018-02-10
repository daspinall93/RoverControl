/*
 * main.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include <stdio.h>
#include <unistd.h>
#include "Locom.h"
#include "Utils.h"

int main(){

	LocomClass Locom;
	Locom.Start();

	Locom.Command.commandid = LOCOM_COMMAND_STRAIGHT_FORWARD;
	Locom.Command.newCommand = true;
	Locom.Command.durmsec = 5000;
	Locom.Command.power = 50;

	Locom.Execute();
	fflush(stdout);
	sleep(2);

	Locom.Execute();
	fflush(stdout);
	sleep(3);
	Locom.Execute();

	return 1;

}
