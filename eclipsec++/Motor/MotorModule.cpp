/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

/* INCLUDE HEADER FILE */
#include "MotorModule.h"

/* INCLUDE EXTERNAL LIBRARIES */
#include <stdio.h>
#include <bcm2835.h>

/* INCLUDE ENUMERATIONS */
#include "../mavlink/v2.0/SoteriaRover/mavlink.h"

/* PIN CONSTANTS */
#define ENA 18	//PWM
#define ENB 19	//PWM
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2

MotorModule::MotorModule()
{
    /* INITIALISE ALL DATA TO 0 */
    memset(&Report, 0, sizeof(Report));
    memset(&Command, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Config));
    memset(&State, 0, sizeof(State));
}

void MotorModule::Start(uint8_t motorid)
{
    /* ASSIGNING PINS */
    Config.motorid = motorid;
    if (motorid==1)
    {
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

    /* SETTING PWM RANGE */
    Config.pwmRange = PWM_RANGE;

    /* SETUP PIN FUNCTIONS */
    bcm2835_gpio_fsel(Config.inPin1 , BCM2835_GPIO_FSEL_OUTP);	//Basic out function
    bcm2835_gpio_fsel(Config.inPin2, BCM2835_GPIO_FSEL_OUTP);

#if PWM_ENABLED
    bcm2835_gpio_fsel(Config.pwmPin, BCM2835_GPIO_FSEL_ALT5);	//PWM functionality
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(Config.pwmChannel, 1, 1);
    bcm2835_pwm_set_range(Config.pwmChannel, PWM_RANGE);
#else
    bcm2835_gpio_fsel(Config.pwmPin, BCM2835_GPIO_FSEL_OUTP);
#endif

    /* SETTING INITIAL OUTPUT */
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
    /* CHECK IF NEW COMMAND HAS BEEN ISSUED FROM LOCOM */
    if (Command.newCommand)
    {
	switch(Command.commandid)
	{

	    case MOTOR_COMMAND_STOP:

		    ModeStop();
		    break;

	    case MOTOR_COMMAND_FORWARD:

		    ModeForward();
		    break;

	    case MOTOR_COMMAND_BACKWARD:

		    ModeBackward();
		    break;


	    default:

		break;

	}

	/* RESET NEW COMMAND FLAG */
	Command.newCommand = 0;	//set to 0 as new command has been processed

    }

    Debug();
}

void MotorModule::ModeStop()
{
    /* SET THE DIRECTION OF MOTOR */
    bcm2835_gpio_write(Config.inPin1, LOW);
    bcm2835_gpio_write(Config.inPin2, LOW);

    /* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
    //calculate the appropriate pwm value depending on the
    bcm2835_pwm_set_data(Config.pwmChannel, 0);
#else
    bcm2835_gpio_write(Config.pwmPin, LOW);
#endif

    /* UPDATE THE STATE */
    State.mode = MOTOR_MODE_STOP;
    State.speed = Command.power;
}

void MotorModule::ModeForward()
{
    bcm2835_gpio_write(Config.inPin1, HIGH);
    bcm2835_gpio_write(Config.inPin2, LOW);

#if PWM_ENABLED
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
	bcm2835_gpio_write(Config.inPin1, LOW);
	bcm2835_gpio_write(Config.inPin2, HIGH);

#if PWM_ENABLED
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

