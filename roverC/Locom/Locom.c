/*
 * Locom.c
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

#include "Locom.h"

/* OTHER MODULES */
#include <bcm2835.h>

/* CONSTANTS */
#include "../mavlink/v2.0/SoteriaRover/mavlink.h"
#define ENA 18	//PWM
#define ENB 19	//PWM
//M1=right motor
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
//M2 = left motor
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2
#define PWM_ENABLED 0
#define PWM_RANGE 1024

/* IMPLEMENTATION DATA */
typedef struct
{
	long int modeStartTime;
	long int modeElapsedTime;
	uint8_t mode;
} Locom_StateStruct;

typedef struct
{

} Locom_ConfigStruct;

static Locom_StateStruct Locom_State;
static Locom_ConfigStruct Locom_Config;

/* IMPLEMENTATION FUNCTIONS */
static void Locom_ModeExecute();


/* INTERFACE FUNCTIONS */
void Locom_Start()
{

    /* SET THE PIN FUNCTIONS */
    bcm2835_gpio_fsel(IN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(IN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(IN3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(IN4, BCM2835_GPIO_FSEL_OUTP);

    //if pwm is enabled then need to configure the appropriate pin
#if PWM_ENABLED
    bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_gpio_fsel(ENb, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(0, 1, 1);
    bcm2835_pwm_set_mode(1, 1, 1);
    bcm2835_pwm_set_range(0, PWM_RANGE);
    bcm2835_pwm_set_range(1, PWM_RANGE);
#else
    bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_OUTP);
#endif

    /* SET THE PIN INITIAL OUTPUT */
    bcm2835_gpio_write(IN1, LOW);
    bcm2835_gpio_write(IN2, LOW);
    bcm2835_gpio_write(IN3, LOW);
    bcm2835_gpio_write(IN4, LOW);

#if PWM_ENABLED
    bcm2835_pwm_set_data(0, 0);
    bcm2835_pwm_set_data(1, 0);
#else
    bcm2835_gpio_write(ENA, LOW);
    bcm2835_gpio_write(ENB, LOW);
#endif
    Locom_State.mode = MOTOR_MODE_STOP;
}

void Locom_Execute(Locom_Command* p_Locom_Command, Locom_Report* p_Locom_Report)
{

    /* CHECK IF NEW COMMAND HAS BEEN ISSUED */
    if (p_Locom_Command->newCommand){

	/* SWITCH BETWEEN THE DIFFERENT COMMAND ID'S */
	switch(p_Locom_Command->commandid){

	    case LOCOM_COMMAND_STOP:

		    Locom_State.mode = LOCOM_MODE_STOP;
		    break;

	    case LOCOM_COMMAND_STRAIGHT_FORWARD:

		    Locom_State.mode = LOCOM_MODE_STRAIGHT_FORWARD;
		    break;

	    case LOCOM_COMMAND_STRAIGHT_BACKWARD:

		    Locom_State.mode = LOCOM_MODE_STRAIGHT_BACKWARD;
		    break;

	    case LOCOM_COMMAND_TURN_LEFT:

		    Locom_State.mode = LOCOM_MODE_TURN_LEFT;
		    break;

	    case LOCOM_COMMAND_TURN_RIGHT:

		    Locom_State.mode = LOCOM_MODE_TURN_RIGHT;
		    break;

	    default:

		    break;

	}

	/* SET START COMMAND START TIME */
	Locom_State.modeStartTime = utils_getTimems();
	Locom_State.modeElapsedTime = 0;

	/* RESET NEW COMMAND FLAG */
	p_Locom_Command->newCommand = 0;

	/* EXECUTE NEW MODE */
	Locom_ModeExecute();
    }
    else
    {
	/* NO NEW COMMAND SO CHECK IF CURRENT COMMAND HAS FINISHED */
	Locom_State.modeElapsedTime = (utils_getTimems() - Locom_State.modeStartTime);
	if(Locom_State >= p_Locom_Command->durmsec)
	{
	    /* COMMAND FINISHED SO RETURN TO STOP MODE */
	    Locom_State.mode = LOCOM_MODE_STOP;
	    Locom_State.modeElapsedTime = 0;

	    /* EXECUTE NEW MODE */
	    Locom_ModeExecute();
	}

    }

}

void Locom_ModeExecute()
{
    /* SWITCH DIRECTION ON THE NEW MODE */
    switch (Locom_State.mode)
    {
	case LOCOM_MODE_STOP:

	    bcm2835_gpio_write(IN1, LOW);
	    bcm2835_gpio_write(IN2, LOW);
	    bcm2835_gpio_write(IN3, LOW);
	    bcm2835_gpio_write(IN4, LOW);

	    break;

	case LOCOM_MODE_STRAIGHT_FORWARD:

	    bcm2835_gpio_write(IN1, HIGH);
	    bcm2835_gpio_write(IN2, LOW);
	    bcm2835_gpio_write(IN3, HIGH);
	    bcm2835_gpio_write(IN4, LOW);

	    break;

	case LOCOM_MODE_STRAIGHT_BACKWARD:

	    bcm2835_gpio_write(IN1, LOW);
	    bcm2835_gpio_write(IN2, HIGH);
	    bcm2835_gpio_write(IN3, LOW);
	    bcm2835_gpio_write(IN4, HIGH);

	    break;

	case LOCOM_MODE_TURN_LEFT:

	    bcm2835_gpio_write(IN1, LOW);
	    bcm2835_gpio_write(IN2, HIGH);
	    bcm2835_gpio_write(IN3, HIGH);
	    bcm2835_gpio_write(IN4, LOW);

	    break;

	case LOCOM_MODE_TURN_RIGHT:

	    bcm2835_gpio_write(IN1, HIGH);
	    bcm2835_gpio_write(IN2, LOW);
	    bcm2835_gpio_write(IN3, LOW);
	    bcm2835_gpio_write(IN4, HIGH);

	    break;

	default:


    }

    /* SET THE POWER USING PWM */
#if PWM_ENABLED

#else
    bcm2835_gpio_write(ENA, HIGH);
    bcm2835_gpio_write(ENB, HIGH);
#endif


}
