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

/* PIN CONSTANTS */
#define ENA 18	//PWM
#define ENB 19	//PWM
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2

#define MOTORS_ENABLED 0
#define PWM_ENABLED 0
#define PWM_RANGE 1024

void MotorModule::Start()
{
	/* ASSIGNING PINS */
	m1_pwmPin = ENA;
	m1_inPin1 = IN1;
	m1_inPin2 = IN2;
	m1_pwmChannel = 0;

	m2_pwmPin = ENB;
	m2_inPin1 = IN3;
	m2_inPin2 = IN4;
	m2_pwmChannel = 1;

	/* SETTING PWM RANGE */
	pwmRange = PWM_RANGE;

#if MOTORS_ENABLED
	/* SETUP PIN FUNCTIONS */
	bcm2835_gpio_fsel(m1_inPin1, BCM2835_GPIO_FSEL_OUTP); //Basic out function
	bcm2835_gpio_fsel(m1_inPin2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(m2_inPin1, BCM2835_GPIO_FSEL_OUTP); //Basic out function
	bcm2835_gpio_fsel(m2_inPin2, BCM2835_GPIO_FSEL_OUTP);

#if PWM_ENABLED
	bcm2835_gpio_fsel(m1_pwmPin, BCM2835_GPIO_FSEL_ALT5); //PWM functionality
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
	bcm2835_pwm_set_mode(m1_pwmChannel, 1, 1);
	bcm2835_pwm_set_range(m1_pwmChannel, pwmRange);

	bcm2835_gpio_fsel(m2_pwmPin, BCM2835_GPIO_FSEL_ALT5); //PWM functionality
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
	bcm2835_pwm_set_mode(m2_pwmChannel, 1, 1);
	bcm2835_pwm_set_range(m2_pwmChannel, pwmRange);
#else
	bcm2835_gpio_fsel(m1_pwmPin, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(m2_pwmPin, BCM2835_GPIO_FSEL_OUTP);
#endif

	/* SETTING INITIAL OUTPUT */
	bcm2835_gpio_write(m1_inPin1, LOW);
	bcm2835_gpio_write(m1_inPin2, LOW);

	bcm2835_gpio_write(m2_inPin1, LOW);
	bcm2835_gpio_write(m2_inPin2, LOW);

#if PWM_ENABLED
	bcm2835_pwm_set_data(m1_pwmChannel, 0);
	bcm2835_pwm_set_data(m2_pwmChannel, 0);
#else
	bcm2835_gpio_write(m1_pwmPin, LOW);
	bcm2835_gpio_write(m2_pwmPin, LOW);
#endif
#endif
	m1_mode = MOTOR_MODE_STOP;
	m2_mode = MOTOR_MODE_STOP;
}

void MotorModule::Execute(mavlink_motor_command_t* p_MotorCommand_in,
		mavlink_motor_report_t* p_MotorReport_out)
{
	/* CHECK IF NEW COMMAND HAS BEEN ISSUED FOR MOTOR 1 */
	if (p_MotorCommand_in->m1_newCommand)
	{
		switch (p_MotorCommand_in->m1_commandid)
		{

		case MOTOR_COMMAND_STOP:

			ModeStop(p_MotorCommand_in, 1);
			break;

		case MOTOR_COMMAND_FORWARD:

			ModeForward(p_MotorCommand_in, 1);
			break;

		case MOTOR_COMMAND_BACKWARD:

			ModeBackward(p_MotorCommand_in, 1);
			break;

		default:

			break;

		}

		/* RESET NEW COMMAND FLAG */
		p_MotorCommand_in->m1_newCommand = 0; //set to 0 as new command has been processed

	}

	/* CHECK IF NEW COMMAND HAS BEEN ISSUED FOR MOTOR 2 */
	if (p_MotorCommand_in->m2_newCommand)
	{
		switch (p_MotorCommand_in->m2_commandid)
		{

		case MOTOR_COMMAND_STOP:

			ModeStop(p_MotorCommand_in, 2);
			break;

		case MOTOR_COMMAND_FORWARD:

			ModeForward(p_MotorCommand_in, 2);
			break;

		case MOTOR_COMMAND_BACKWARD:

			ModeBackward(p_MotorCommand_in, 2);
			break;

		default:

			break;

		}

		/* RESET NEW COMMAND FLAG */
		p_MotorCommand_in->m2_newCommand = 0; //set to 0 as new command has been processed

	}

	Debug();
}

void MotorModule::ModeStop(const mavlink_motor_command_t* p_MotorCommand_in,
		uint8_t motorid)
{
	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = 0;

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m1_inPin1, LOW);
		bcm2835_gpio_write(m1_inPin2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m1_pwmChannel, 0);
#else
		bcm2835_gpio_write(m1_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_mode = MOTOR_MODE_STOP;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = 0;

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m2_inPin1, LOW);
		bcm2835_gpio_write(m2_inPin2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m2_pwmChannel, 0);
#else
		bcm2835_gpio_write(m2_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_mode = MOTOR_MODE_STOP;
		break;

	}
}

void MotorModule::ModeForward(const mavlink_motor_command_t* p_MotorCommand_in,
		uint8_t motorid)
{
	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = CalculatepwmData(p_MotorCommand_in->m1_power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m1_inPin1, HIGH);
		bcm2835_gpio_write(m1_inPin2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m1_pwmChannel, 0);
#else
		bcm2835_gpio_write(m1_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_mode = MOTOR_MODE_FORWARD;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = CalculatepwmData(p_MotorCommand_in->m2_power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m2_inPin1, HIGH);
		bcm2835_gpio_write(m2_inPin2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m2_pwmChannel, 0);
#else
		bcm2835_gpio_write(m2_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_mode = MOTOR_MODE_FORWARD;
		break;

	}

}

void MotorModule::ModeBackward(const mavlink_motor_command_t* p_MotorCommand_in,
		uint8_t motorid)
{

	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = CalculatepwmData(p_MotorCommand_in->m1_power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m1_inPin1, LOW);
		bcm2835_gpio_write(m1_inPin2, HIGH);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m1_pwmChannel, 0);
#else
		bcm2835_gpio_write(m1_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_mode = MOTOR_MODE_BACKWARD;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = CalculatepwmData(p_MotorCommand_in->m2_power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(m2_inPin1, LOW);
		bcm2835_gpio_write(m2_inPin2, HIGH);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(m2_pwmChannel, 0);
#else
		bcm2835_gpio_write(m2_pwmPin, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_mode = MOTOR_MODE_BACKWARD;
		break;

	}
}

void MotorModule::UpdateReport(mavlink_motor_report_t* p_MotorReport_out)
{
	p_MotorReport_out->m1_mode = m1_mode;
	p_MotorReport_out->m1_pwmInput = m1_pwmInput;

	p_MotorReport_out->m2_mode = m2_mode;
	p_MotorReport_out->m2_pwmInput = m2_pwmInput;
}

void MotorModule::Debug()
{
	printf("[MOTOR%d]Mode = %d \t pwmInput = %d \n", 1, m1_mode, m1_pwmInput);
	printf("[MOTOR%d]Mode = %d \t pwmInput = %d \n", 2, m2_mode, m2_pwmInput);
}

uint32_t MotorModule::CalculatepwmData(uint32_t power_per)
{
	uint32_t pwmData;
	pwmData = (int) (((float) power_per / 100.0) * (float) pwmRange);
	return pwmData;
}
