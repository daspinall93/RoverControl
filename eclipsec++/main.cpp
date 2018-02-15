/*
 * main.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include <stdio.h>
#include <unistd.h>

#include "CommsModule.h"
#include "LocomModule.h"
#include "Utils.h"

void testLocom();

int main(){
	//bcm2835_initlocom();
	LocomModule Locom;
	CommsModule Comms;
	Comms.Start();
	Locom.Start();

	//set up new send command
	Comms.MavInput.heartBeat.Locom_mode = LOCOM_MODE_STRAIGHT_FORWARD;
	Comms.MavInput.newSendCommand = 1;

	Locom.Execute();

	Comms.Execute();
	sleep(1);
	Comms.Execute();

	//after receiving the command assign it to the input for Locom
	if (Comms.MavOutput.newPacketReceived){
		Locom.Command.commandid = Comms.MavOutput.locomCommand.Locom_commandid;
		Locom.Command.durmsec = Comms.MavOutput.locomCommand.duration_ms;
		Locom.Command.power = Comms.MavOutput.locomCommand.power;
		Locom.Command.newCommand = 1;
	}

	Locom.Execute();

	Comms.Stop();

	return 1;

}

void testLocom(){

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


}


