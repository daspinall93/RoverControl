/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

#include "MotorClass.h"

#include <stdio.h>

void MotorClass::Start(){

	//setup motor outputs

//	bcm2835_gpio_fsel(Parameters.inPin1 , BCM2835_GPIO_FSEL_OUTP);	//Basic out function
//	bcm2835_gpio_fsel(Parameters.inPin2, BCM2835_GPIO_FSEL_OUTP);
//	bcm2835_gpio_fsel(Parameters.pwmPin, BCM2835_GPIO_FSEL_OUTP);
//
//	//initialise motor output
//	bcm2835_gpio_write(Parameters.inPin1, LOW);
//	bcm2835_gpio_write(Parameters.inPin2, LOW);
//	bcm2835_gpio_write(Parameters.pwmPin, LOW);


}

void MotorClass::Execute(){

	if (Command.newCommand){
		switch(Command.commandid){

			case MOTOR_COMMAND_STOP:
				//stay in standby

				ModeStop();
				break;

			case MOTOR_COMMAND_FORWARD:
				//drive straight command

				ModeForward();
				break;

			case MOTOR_COMMAND_BACKWARD:
				//go in a straight line backwards

				//set to drive all wheels backward
				ModeBackward();
				break;


			default:
				//invalid command

				break;

		}

		//reset new command flag
		Command.newCommand = 0;	//set to 0 as new command has been processed

	}

	Debug();

}

void MotorClass::ModeStop(){


	State.mode = MOTOR_MODE_STOP;
	State.speed = Command.power;

}

void MotorClass::ModeForward(){


	State.mode = MOTOR_MODE_FORWARD;
	State.speed = Command.power;

}

void MotorClass::ModeBackward(){


	State.mode = MOTOR_MODE_BACKWARD;
	State.speed = Command.power;

}


void MotorClass::Debug(){

	printf("[MOTOR%d]Mode = %d \t speed = %d \n", Parameters.motorid, State.mode, State.speed);


}
