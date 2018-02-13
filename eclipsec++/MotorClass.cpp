/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

#include "MotorClass.h"

#include <stdio.h>

void MotorClass::Start(uint8_t inPin1, uint8_t inPin2, uint8_t pwmPin, uint8_t motorid, uint8_t pwmChannel){

	Config.motorid = motorid;
	Config.pwmPin = pwmPin;
	Config.inPin1 = inPin1;
	Config.inPin2 = inPin2;
	Config.pwmRange = PWM_RANGE;

	//setup motor outputs
	bcm2835_gpio_fsel(Config.inPin1 , BCM2835_GPIO_FSEL_OUTP);	//Basic out function
	bcm2835_gpio_fsel(Config.inPin2, BCM2835_GPIO_FSEL_OUTP);

	//if pwm is enabled then need to configure the appropriate pin
#if PWM_ENABLED
	bcm2835_gpio_fsel(Config.pwmPin, BCM2835_GPIO_FSEL_ALT5);	//PWM functionality
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(Config.pwmChannel, 1, 1);
    bcm2835_pwm_set_range(Config.pwmChannel, PWM_RANGE);
#else
	bcm2835_gpio_fsel(Config.pwmPin, BCM2835_GPIO_FSEL_OUTP);
#endif

	//initialise motor output
	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, LOW);

#ifdef PWM_ENABLED
	bcm2835_pwm_set_data(Config.pwmChannel, 0);
#else
	bcm2835_gpio_write(Config.pwmPin, LOW);
	State.mode = MOTOR_MODE_STOP;
#endif

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

#ifdef PWM_ENABLED
	//calculate the appropriate pwm value depending on the
#else
	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, LOW);
	bcm2835_gpio_write(Config.pwmPin, LOW);
#endif
	State.mode = MOTOR_MODE_STOP;
	State.speed = Command.power;

}

void MotorClass::ModeForward(){

	bcm2835_gpio_write(Config.inPin1, HIGH);
	bcm2835_gpio_write(Config.inPin2, LOW);
	bcm2835_gpio_write(Config.pwmPin, HIGH);
	State.mode = MOTOR_MODE_FORWARD;
	State.speed = Command.power;

}

void MotorClass::ModeBackward(){

	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, HIGH);
	bcm2835_gpio_write(Config.pwmPin, HIGH);
	State.mode = MOTOR_MODE_BACKWARD;
	State.speed = Command.power;

}


void MotorClass::Debug(){

	printf("[MOTOR%d]Mode = %d \t speed = %d \n", Config.motorid, State.mode, State.speed);


}
