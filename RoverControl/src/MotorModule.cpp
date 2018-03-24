/*
 * Motor.cpp
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

/* INCLUDE HEADER FILE */
#include "MotorModule.h"
#include "Utils.h"

/* INCLUDE EXTERNAL LIBRARIES */
#include <stdio.h>
#include <iostream>
#include <bcm2835.h>

/* PIN CONSTANTS */
#define M1_PWMPIN 18	//PWM 5
#define M2_PWMPIN 19	//PWM 6
#define M1_INPIN1 17	//dig for M1 8
#define M1_INPIN2 4	//dig for M1 7
#define M2_INPIN1 22	//dig for M2 12
#define M2_INPIN2 27	//dig for M2 13
#define M1_PWM_CHANNEL 0
#define M2_PWM_CHANNEL 1

#define PWM_ENABLED 1
#define PWM_RANGE 1024

void MotorModule::Start()
{

	std::cout << "[MOTOR]Starting Module..." << std::endl;

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

	m1_subMode = MOTOR_SUBMODE_STOP;
	m2_subMode = MOTOR_SUBMODE_STOP;
	mode = MOTOR_MODE_STOP;

	modeStartTime_ms = Utils::GetTimems();

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
			ModeStop(p_MotorCommand_in);

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

	}

	Debug();
}

void MotorModule::Stop()
{
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

}

void MotorModule::ModeStop(mavlink_motor_command_t* p_MotorCommand_in)
{
	/* M1 = STOP
	 * M2 = STOP
	 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m1_pwmInput = 0;

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M1_INPIN1, LOW);
	bcm2835_gpio_write(M1_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, 0);
#else
	bcm2835_gpio_write(M1_PWMPIN, LOW);
#endif

	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m2_pwmInput = 0;

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M2_INPIN1, LOW);
	bcm2835_gpio_write(M2_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, 0);
#else
	bcm2835_gpio_write(M2_PWMPIN, LOW);
#endif

	/* UPDATE THE STATE */
	m1_subMode = MOTOR_SUBMODE_STOP;
	m2_subMode = MOTOR_SUBMODE_STOP;

	mode = MOTOR_MODE_STOP;
}

void MotorModule::ModeStraightForward(
		mavlink_motor_command_t* p_MotorCommand_in)
{
	/* M1 = FORWARD
	 * M2 = FORWARD
	 */

	/* UPDATE M1 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M1_INPIN1, HIGH);
	bcm2835_gpio_write(M1_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M1_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m1_subMode = MOTOR_SUBMODE_FORWARD;

	/* UPDATE M2 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M2_INPIN1, HIGH);
	bcm2835_gpio_write(M2_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M2_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m2_subMode = MOTOR_SUBMODE_FORWARD;

	/* UPDATE MODE */
	mode = MOTOR_MODE_STRAIGHT_FORWARD;
}

void MotorModule::ModeStraightBackward(
		mavlink_motor_command_t* p_MotorCommand_in)
{
	/* M1 = BACKWARD
	 * M2 = BACKWARD
	 */

	/* UPDATE M1 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M1_INPIN1, LOW);
	bcm2835_gpio_write(M1_INPIN2, HIGH);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M1_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m1_subMode = MOTOR_SUBMODE_BACKWARD;

	/* UPDATE M2 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M2_INPIN1, LOW);
	bcm2835_gpio_write(M2_INPIN2, HIGH);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M2_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m2_subMode = MOTOR_SUBMODE_BACKWARD;

	/* UPDATE MODE */
	mode = MOTOR_MODE_STRAIGHT_BACKWARD;
}

void MotorModule::ModeTurnRight(mavlink_motor_command_t* p_MotorCommand_in)
{
	/* M1 = FORWARD
	 * M2 = BACKWARD
	 */

	/* UPDATE M1 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M1_INPIN1, HIGH);
	bcm2835_gpio_write(M1_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M1_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m1_subMode = MOTOR_SUBMODE_FORWARD;

	/* UPDATE M2 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M2_INPIN1, LOW);
	bcm2835_gpio_write(M2_INPIN2, HIGH);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M2_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m2_subMode = MOTOR_SUBMODE_BACKWARD;

	/* UPDATE MODE */
	mode = MOTOR_MODE_TURN_RIGHT;
}

void MotorModule::ModeTurnLeft(mavlink_motor_command_t* p_MotorCommand_in)
{
	/* M1 = BACKWARD
	 * M2 = FORWARD
	 */

	/* UPDATE M1 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m1_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M1_INPIN1, LOW);
	bcm2835_gpio_write(M1_INPIN2, HIGH);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M1_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M1_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m1_subMode = MOTOR_SUBMODE_BACKWARD;

	/* UPDATE M2 */
	/* CALCULATE PWM INPUT FROM THE INPUT COMMAND */
	m2_pwmInput = CalculatepwmData(p_MotorCommand_in->power_per);

	/* SET THE DIRECTION OF MOTOR */
	bcm2835_gpio_write(M2_INPIN1, HIGH);
	bcm2835_gpio_write(M2_INPIN2, LOW);

	/* SET THE OUTPUT AVERAGE VOLTAGE */
#if PWM_ENABLED
	bcm2835_pwm_set_data(M2_PWM_CHANNEL, m1_pwmInput);
#else
	bcm2835_gpio_write(M2_PWMPIN, HIGH);
#endif

	/* UPDATE THE SUB MODE */
	m2_subMode = MOTOR_SUBMODE_FORWARD;

	/* UPDATE MODE */
	mode = MOTOR_MODE_TURN_LEFT;
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
