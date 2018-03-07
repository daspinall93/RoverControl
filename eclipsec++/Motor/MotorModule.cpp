/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

/* INCLUDE HEADER FILE */
#include "MotorModule.h"
#include "../Utils/Utils.h"

/* INCLUDE EXTERNAL LIBRARIES */
#include <stdio.h>
#include <bcm2835.h>

/* PIN CONSTANTS */
#define M1_PWMPIN 18	//PWM
#define M2_PWMPIN 19	//PWM
#define M1_INPIN1 4	//dig for M1
#define M1_INPIN2 17	//dig for M1
#define M2_INPIN1 27	//dig for M2
#define M2_INPIN2 22	//dig for M2
#define M1_PWM_CHANNEL 0
#define M2_PWM_CHANNEL 1

#define MOTORS_ENABLED 0
#define PWM_ENABLED 1
#define PWM_RANGE 1024

void MotorModule::Start()
{
#if MOTORS_ENABLED
	/* SETUP PIN FUNCTIONS */
	bcm2835_gpio_fsel(M1_INPIN1, BCM2835_GPIO_FSEL_OUTP); //Basic out function
	bcm2835_gpio_fsel(M1_INPIN2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(M2_INPIN1, BCM2835_GPIO_FSEL_OUTP); //Basic out function
	bcm2835_gpio_fsel(M2_INPIN2, BCM2835_GPIO_FSEL_OUTP);

#if PWM_ENABLED
	bcm2835_gpio_fsel(M1_PWMPIN, BCM2835_GPIO_FSEL_ALT5); //PWM functionality
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
	bcm2835_pwm_set_mode(M1_PWM_CHANNEL, 1, 1);
	bcm2835_pwm_set_range(M1_PWM_CHANNEL, PWM_RANGE);

	bcm2835_gpio_fsel(M2_PWMPIN, BCM2835_GPIO_FSEL_ALT5); //PWM functionality
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
	bcm2835_pwm_set_mode(M2_PWM_CHANNEL, 1, 1);
	bcm2835_pwm_set_range(M2_PWM_CHANNEL, PWM_RANGE);
#else
	bcm2835_gpio_fsel(M1_PWMPIN, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(M2_PWMPIN, BCM2835_GPIO_FSEL_OUTP);
#endif

	/* SETTING INITIAL OUTPUT */
	bcm2835_gpio_write(M1_INPIN1, LOW);
	bcm2835_gpio_write(M1_INPIN2, LOW);

	bcm2835_gpio_write(M2_INPIN1, LOW);
	bcm2835_gpio_write(M2_INPIN2, LOW);

#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
	bcm2835_gpio_write(M1_PWMPIN, LOW);
	bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif
#endif
	m1_subMode = MOTOR_MODE_STOP;
	m2_subMode = MOTOR_MODE_STOP;
}

void MotorModule::Execute(mavlink_motor_command_t* p_MotorCommand_in,
		mavlink_motor_report_t* p_MotorReport_out)
{
	//Debug();

	/* CHECK IF NEW COMMAND HAS BEEN ISSUED */
	if (p_MotorCommand_in->newCommand)
	{
		/* SWITCH ON THE COMMAND ID */
		switch (p_MotorCommand_in->commandid)
		{
		case MOTOR_COMMAND_STOP:

			/* SET THE SUB MODE FOR EACH MOTOR */
			SubModeStop(p_MotorCommand_in, 1);
			SubModeStop(p_MotorCommand_in, 2);

			break;

		case MOTOR_COMMAND_STRAIGHT_FORWARD:

			ModeStraightForward(p_MotorCommand_in);
			break;

		case MOTOR_COMMAND_STRAIGHT_BACKWARD:

			ModeStraightBackward(p_MotorCommand_in);
			break;

		case MOTOR_COMMAND_TURN_LEFT:

			ModeTurnLeft(p_MotorCommand_in);
			break;

		case MOTOR_COMMAND_TURN_RIGHT:

			ModeTurnRight(p_MotorCommand_in);
			break;

		default:

			break;

		}

		/* INITALISE THE TIMER FOR THE COMMAND */
		modeStartTime_ms = Utils::GetTimems();
		modeElapsedTime_ms = 0;

	}
	else
	{

		/* UPDATE ELAPSED TIME */
		modeElapsedTime_ms = (Utils::GetTimems() - modeStartTime_ms);

		/* CHECK IF THE COMMAND HAS FINISHED */
		if (modeElapsedTime_ms >= p_MotorCommand_in->duration_ms)
		{
			/* RESET TIMER AND SET MODE TO STOP */
			modeStartTime_ms = Utils::GetTimems();
			modeElapsedTime_ms = 0;
			ModeStop(p_MotorCommand_in);

		}

	}
	//execute the changes for the motors
	Debug();
}

void MotorModule::Stop()
{
#if MOTORS_ENABLED
	/* SET ALL OUTPUTS LOW */
	bcm2835_gpio_write(M1_INPIN1, LOW);
	bcm2835_gpio_write(M1_INPIN2, LOW);
	bcm2835_gpio_write(M2_INPIN1, LOW);
	bcm2835_gpio_write(M2_INPIN2, LOW);
#if PWM_ENABLED
		bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
		bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M1_PWMPIN, LOW);
		bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif

	/* SET ALL PINS TO INPUTS */
	bcm2835_gpio_fsel(M1_INPIN1, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(M1_INPIN2, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(M2_INPIN1, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(M2_INPIN2, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(M2_PWMPIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_fsel(M1_PWMPIN, BCM2835_GPIO_FSEL_INPT);
#endif
}

void MotorModule::ModeStop(mavlink_motor_command_t* p_MotorCommand_in)
{
	/* ASSIGN THE MODES FOR THE MOTORS */
	SubModeStop(p_MotorCommand_in, 1);
	SubModeStop(p_MotorCommand_in, 2);

	mode = MOTOR_MODE_STOP;
}

void MotorModule::ModeStraightForward(
		mavlink_motor_command_t* p_MotorCommand_in)
{
	/* ASSIGN THE MODES FOR THE MOTORS */
	SubModeForward(p_MotorCommand_in, 1);
	SubModeForward(p_MotorCommand_in, 2);

	mode = MOTOR_MODE_STRAIGHT_FORWARD;
}

void MotorModule::ModeStraightBackward(
		mavlink_motor_command_t* p_MotorCommand_in)
{
	/* ASSIGN THE MODES FOR THE MOTORS */
	SubModeBackward(p_MotorCommand_in, 1);
	SubModeBackward(p_MotorCommand_in, 2);

	mode = MOTOR_MODE_STRAIGHT_BACKWARD;
}

void MotorModule::ModeTurnRight(mavlink_motor_command_t* p_MotorCommand_in)
{

	/* ASSIGN THE MODES FOR THE MOTORS */
	SubModeForward(p_MotorCommand_in, 1);
	SubModeBackward(p_MotorCommand_in, 2);

	mode = MOTOR_MODE_TURN_RIGHT;
}

void MotorModule::ModeTurnLeft(mavlink_motor_command_t* p_MotorCommand_in)
{

	/* ASSIGN THE MODES FOR THE MOTORS */
	SubModeBackward(p_MotorCommand_in, 1);
	SubModeForward(p_MotorCommand_in, 2);

	mode = MOTOR_MODE_TURN_LEFT;
}

void MotorModule::SubModeStop(const mavlink_motor_command_t* p_MotorCommand_in,
		uint8_t motorid)
{
	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = 0;

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M1_INPIN1, LOW);
		bcm2835_gpio_write(M1_INPIN2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M1_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_subMode = MOTOR_SUBMODE_STOP;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = 0;

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M2_INPIN1, LOW);
		bcm2835_gpio_write(M2_INPIN2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_subMode = MOTOR_SUBMODE_STOP;
		break;

	}
}

void MotorModule::SubModeForward(
		const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid)
{
	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M1_INPIN1, HIGH);
		bcm2835_gpio_write(M1_INPIN2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M1_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_subMode = MOTOR_SUBMODE_FORWARD;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M2_INPIN1, HIGH);
		bcm2835_gpio_write(M2_INPIN2, LOW);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_subMode = MOTOR_SUBMODE_FORWARD;
		break;

	}

}

void MotorModule::SubModeBackward(
		const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid)
{

	switch (motorid)
	{
	case 1:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M1_INPIN1, LOW);
		bcm2835_gpio_write(M1_INPIN2, HIGH);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M1_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m1_subMode = MOTOR_SUBMODE_BACKWARD;
		break;

	case 2:
		/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
		m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

#if MOTORS_ENABLED
		/* SET THE DIRECTION OF MOTOR */
		bcm2835_gpio_write(M2_INPIN1, LOW);
		bcm2835_gpio_write(M2_INPIN2, HIGH);

		/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
		bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
		bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif
#endif

		/* UPDATE THE STATE */
		m2_subMode = MOTOR_SUBMODE_BACKWARD;
		break;

	}
}

void MotorModule::UpdateReport(mavlink_motor_report_t* p_MotorReport_out)
{
	p_MotorReport_out->m1_sub_mode = m1_subMode;
	p_MotorReport_out->m1_pwmInput = m1_pwmInput;

	p_MotorReport_out->m2_sub_mode = m2_subMode;
	p_MotorReport_out->m2_pwmInput = m2_pwmInput;

	p_MotorReport_out->mode = mode;
	p_MotorReport_out->modeElapsedTime_ms = modeElapsedTime_ms;
}

void MotorModule::Debug()
{
	printf("[MOTOR]Mode = %d \t Time elapsed = %ld \n", mode,
			modeElapsedTime_ms);
	printf("[MOTOR%d]Mode = %d \t pwmInput = %d \n", 1, m1_subMode,
			m1_pwmInput);
	printf("[MOTOR%d]Mode = %d \t pwmInput = %d \n", 2, m2_subMode,
			m2_pwmInput);
}

uint32_t MotorModule::CalculatepwmData(uint32_t power_per)
{
	uint32_t pwmData;
	pwmData = (int) (((float) power_per / 100.0) * (float) PWM_RANGE);
	return pwmData;
}
