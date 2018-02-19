/*
 * Locom_privateFunctions.h
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

/* INCLUDE MAVLINK HEADER WHICH CONTAINS ENUMERATIONS */

/* LOCOM INCLUDES */
#include "Locom_privateConst.h"
#include "Locom_privateStructs.h"
#include "Locom_publicStructs.h"

void Locom_SubModeTransition(locom_comConfStruct* p_locom_command,
                             locom_internStateStruct* p_locom_state)
{

    /* CHECK IF NEW COMMAND HAS BEEN ISSUED */
    if (p_locom_command->newCommand){

	/* SWITCH BETWEEN THE DIFFERENT COMMAND ID'S */
	switch(p_locom_command->command){

	    case LOCOM_COMMAND_STOP:

		    p_locom_state->locomSubMode = LOCOM_MODE_STOP;
		    break;

	    case LOCOM_COMMAND_STRAIGHT_FORWARD:

		    p_locom_state->locomSubMode = LOCOM_MODE_STRAIGHT_FORWARD;
		    break;

	    case LOCOM_COMMAND_STRAIGHT_BACKWARD:

		    p_locom_state->locomSubMode = LOCOM_MODE_STRAIGHT_BACKWARD;
		    break;

	    case LOCOM_COMMAND_TURN_LEFT:

		    p_locom_state->locomSubMode = LOCOM_MODE_TURN_LEFT;
		    break;

	    case LOCOM_COMMAND_TURN_RIGHT:

		    locom_internState.locomSubMode = LOCOM_STATE_TURN_RIGHT;
		    break;

	    default:

		    break;

	}

	/* SET START COMMAND START TIME */
	locom_internState.comStartTimems = utils_getTimems();
	locom_internState.comElapsedTimems = 0;

	/* RESET NEW COMMAND FLAG */
	p_locom_command->newCommand = 0;

    }
    else
    {
	/* NO NEW COMMAND SO CHECK IF CURRENT COMMAND HAS FINISHED */
	p_locom_state->comElapsedTimems = (utils_getTimems() - p_locom_state->comStartTimems);
	if(p_locom_state->comElapsedTimems >= p_locom_command->msecDur){

	    /* COMMAND FINISHED SO RETURN TO STOP MODE */
	    locom_internState.locomSubMode = LOCOM_MODE_STOP;
	    locom_internState.comElapsedTimems = 0;

	}

    }

}

void Locom_GenStatRep(locom_statRepStruct* p_locom_statRep)
{
	//generate the latest state report
	p_locom_statRep->locomSubMode = locom_internState.locomSubMode;
	p_locom_statRep->comElapsedTimems = locom_internState.comElapsedTimems;

}

void Locom_SubModeAction(locom_comConfStruct* p_locom_command)
{

    switch (locom_internState.locomLeftWheel){

	case LOCOM_WHEEL_FORWARD:

	    bcm2835_gpio_write(IN1, HIGH);
	    bcm2835_gpio_write(IN2, LOW);
	    break;

	case LOCOM_WHEEL_BACKWARD:

	    bcm2835_gpio_write(IN1, LOW);
	    bcm2835_gpio_write(IN2, HIGH);
	    break;

	case LOCOM_WHEEL_STOP:

	    bcm2835_gpio_write(IN1, LOW);
	    bcm2835_gpio_write(IN2, LOW);
	    break;

    }

    switch (locom_internState.locomRightWheel){

	case LOCOM_WHEEL_FORWARD:

	    bcm2835_gpio_write(IN3, HIGH);
	    bcm2835_gpio_write(IN4, LOW);
	    break;

	case LOCOM_WHEEL_BACKWARD:

	    bcm2835_gpio_write(IN3, LOW);
	    bcm2835_gpio_write(IN4, HIGH);
	    break;

	case LOCOM_WHEEL_STOP:

	    bcm2835_gpio_write(IN3, LOW);
	    bcm2835_gpio_write(IN4, LOW);
	    break;

    }

}


