/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */
#include "Locom.h"

#include <bcm2835.h>

void LocomClass::Start(){

//	//setup motor outputs
//	bcm2835_gpio_fsel(IN1, BCM2835_GPIO_FSEL_OUTP);	//Basic out function
//	bcm2835_gpio_fsel(IN2, BCM2835_GPIO_FSEL_OUTP);
//	bcm2835_gpio_fsel(IN3, BCM2835_GPIO_FSEL_OUTP);
//	bcm2835_gpio_fsel(IN4, BCM2835_GPIO_FSEL_OUTP);
//	bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);	//use 5v or 0 for the pwm output
//	bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_OUTP);
//
//	bcm2835_gpio_write(IN1, LOW);
//	bcm2835_gpio_write(IN2, LOW);
//	bcm2835_gpio_write(IN3, LOW);
//	bcm2835_gpio_write(IN4, LOW);
//	bcm2835_gpio_write(ENA, HIGH);
//	bcm2835_gpio_write(ENB, HIGH);

	//initialise the state structure
	State.mode = LOCOM_MODE_STOP;
	State.modeElapsedTime = 0;
	State.modeStartTime = 0;

}

void LocomClass::Execute(){

	Debug();

	if (Command.newCommand){
		switch(Command.commandid){

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

	}else{

		//no new command so need to check time elapsed
		State.modeElapsedTime = (utils_getTimems() - State.modeStartTime);
		if(State.modeElapsedTime >= Command.durmsec){
			//the command has ended so turn of motors and reset elapsed time

			State.modeStartTime = utils_getTimems();;
			State.modeElapsedTime = 0;
			ModeStop();

		}

	}

	Debug();
}

/*
 * Private function to put the rover into the stop mode
 */
void LocomClass::ModeStop(){

	State.mode = LOCOM_MODE_STOP;

}

/*
 * Private function to put the rover into the drive straight forward mode
 */
void LocomClass::ModeStraightForward(){

	State.mode = LOCOM_MODE_STRAIGHT_FORWARD;


}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomClass::ModeStraightBackward(){

	State.mode = LOCOM_MODE_STRAIGHT_FORWARD;

}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomClass::ModeTurnRight(){

	State.mode = LOCOM_MODE_TURN_RIGHT;

}

/*
 * Private function to put the rover into the drive straight backward mode
 */
void LocomClass::ModeTurnLeft(){

	State.mode = LOCOM_MODE_TURN_LEFT;

}

void LocomClass::UpdateReport(){

	Report.mode = State.mode;

}

void LocomClass::Debug(){

	printf("Mode = %d \t T elapsed = %ld \n", State.mode, State.modeElapsedTime);

}



