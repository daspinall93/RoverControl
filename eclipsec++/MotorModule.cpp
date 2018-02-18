/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

#include "MotorModule.h"

#include <stdio.h>
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

void MotorModule::Start(uint8_t motorid)
{
	//set configuration according to the motorid given
	Config.motorid = motorid;

	if (motorid==1){
		Config.pwmPin = ENA;
		Config.inPin1 = IN1;
		Config.inPin2 = IN2;
		Config.pwmChannel = 0;
	}
	else if (motorid==2)
	{
		Config.pwmPin = ENA;
		Config.inPin1 = IN1;
		Config.inPin2 = IN2;
		Config.pwmChannel = 1;
	}
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

#if PWM_ENABLED
	bcm2835_pwm_set_data(Config.pwmChannel, 0);
#else
	bcm2835_gpio_write(Config.pwmPin, LOW);
	State.mode = MOTOR_MODE_STOP;
#endif

}

void MotorModule::Execute()
{
	if (Command.newCommand)
	{
		switch(Command.commandid)
		{

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

void MotorModule::ModeStop()
{
	//the direction of the outputted voltage
	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, LOW);

	//set the magnitude of the average output voltage
#if PWM_ENABLED
	//calculate the appropriate pwm value depending on the
	bcm2835_pwm_set_data(Config.pwmChannel, 0);
#else
	bcm2835_gpio_write(Config.pwmPin, LOW);
#endif
	State.mode = MOTOR_MODE_STOP;
	State.speed = Command.power;
}

void MotorModule::ModeForward()
{
	//set direction of the outputted voltage
	bcm2835_gpio_write(Config.inPin1, HIGH);
	bcm2835_gpio_write(Config.inPin2, LOW);

	//set the magnitude of the average output voltage
#if PWM_ENABLED
	//calculate the appropriate pwm value depending on the
	Command.pwmData = (int) (Command.power / 100) * Config.pwmRange;
	bcm2835_pwm_set_data(Config.pwmChannel, Command.pwmData);
#else

	bcm2835_gpio_write(Config.pwmPin, HIGH);
#endif

	State.mode = MOTOR_MODE_FORWARD;
	State.speed = Command.power;
}

void MotorModule::ModeBackward()
{
	//set direction of the outputted voltage
	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, HIGH);

	//set the magnitude of the average outputted voltage
#if PWM_ENABLED
	//calculate the appropriate pwm value depending on the
	Command.pwmData = (int) (Command.power / 100) * Config.pwmRange;
	bcm2835_pwm_set_data(Config.pwmChannel, Command.pwmData);
#else

	bcm2835_gpio_write(Config.pwmPin, HIGH);
#endif

	State.mode = MOTOR_MODE_BACKWARD;
	State.speed = Command.power;
}

void MotorModule::UpdateReport()
{
	Report.mode = State.mode;
}

void MotorModule::Debug()
{
	printf("[MOTOR%d]Mode = %d \t speed = %d \n", Config.motorid, State.mode, State.speed);
}

