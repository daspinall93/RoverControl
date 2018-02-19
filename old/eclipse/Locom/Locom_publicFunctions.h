/*
 * rv_loc.c
 *
 *  Created on: 17 Jan 2018
 *      Author: dan
 */

/* EXTERNAL LIBRARIES */
#include <math.h>
#include <stdio.h>
#include "bcm2835.h"	//interface with motors

/* LOCOM LIBRARIES */
#include "Locom_privateConst.h"
#include "Locom_privateStructs.h"
#include "Locom_privateFunctions.h"

#include "rvUtils.h"	//helpful self-contained functions


#include "Locom_privateFunctions.h"
#include "../mavlink/v2.0/SoteriaRover/mavlink.h"
#include "Locom_publicStructs.h"

//pin defintions
//drive pins

//private data for locom to access
locom_internStateStruct locom_internState;
locom_modConfStruct locom_modConf;

void Locom_Start(){

	//setup motor outputs
	bcm2835_gpio_fsel(IN1, BCM2835_GPIO_FSEL_OUTP);	//Basic out function
	bcm2835_gpio_fsel(IN2, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(IN3, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(IN4, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);	//use 5v or 0 for the pwm output
	bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_OUTP);

	bcm2835_gpio_write(IN1, LOW);
	bcm2835_gpio_write(IN2, LOW);
	bcm2835_gpio_write(IN3, LOW);
	bcm2835_gpio_write(IN4, LOW);
	bcm2835_gpio_write(ENA, HIGH);
	bcm2835_gpio_write(ENB, HIGH);

	//initialise the state structure
	locom_internState.locomSubMode = LOCOM_COMMAND_STOP;
	locom_internState.locomLeftWheel = LOCOM_WHEEL_STOP;
	locom_internState.locomRightWheel = LOCOM_WHEEL_STOP;
	locom_internState.comElapsedTimems = 0;
	locom_internState.comStartTimems = 0;
}

void Locom_Do(locom_comConfStruct* p_locom_comConf, locom_statRepStruct* p_locom_statRep){

	//print out state of the module
	printf("[LOCOM ENTRY]right wheel = %d \t left wheel = %d \n", locom_internState.locomLeftWheel, locom_internState.locomRightWheel);

	//carry out state transition if new command received
	Locom_SubModeTransition(p_locom_comConf);

	//carry out actions depending on new state
	Locom_SubModeAction();

	//generate the status report
	Locom_GenStatRep(p_locom_statRep);

	//printf("[LOCOM EXIT]right wheel = %d \t left wheel = %d \n", locom_internState.locomLeftWheel, locom_internState.locomRightWheel);

}

void locom_stop(){

	//turn of the pins
	bcm2835_gpio_write(ENA, LOW);
	bcm2835_gpio_write(ENB, LOW);

	bcm2835_gpio_write(IN1, LOW);
	bcm2835_gpio_write(IN2, LOW);
	bcm2835_gpio_write(IN3, LOW);
	bcm2835_gpio_write(IN4, LOW);

//	bcm2835_gpio_fsel(IN1, BCM2835_GPIO_FSEL_INPT);	//Basic out function
//	bcm2835_gpio_fsel(IN2, BCM2835_GPIO_FSEL_INPT);
//	bcm2835_gpio_fsel(IN3, BCM2835_GPIO_FSEL_INPT);
//	bcm2835_gpio_fsel(IN4, BCM2835_GPIO_FSEL_INPT);
//	bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_INPT);	//use 5v or 0 for the pwm output
//	bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_INPT);

}

//private functions




//void locom_stateTrans(){
//
//	//check that a transition is actually occuring
//	if (locom_statRep.locomNextState == locom_statRep.locomState){
//		//do nothing
//		return;
//
//
//	}else{
//
//		switch(locom_statRep.locomNextState){
//
//			//for now transitions will involve just changin the state
//
//			case LOCOM_COMMAND_STOP:
//				locom_statRep.locomState = LOCOM_STATE_STOP;
//
//				break;
//
//			case LOCOM_STATE_STRAIGHT_FORWARD:
//				locom_statRep.locomState = LOCOM_STATE_STRAIGHT_FORWARD;
//
//				break;
//
//			case LOCOM_STATE_STRAIGHT_BACKWARD:
//				locom_statRep.locomState = LOCOM_STATE_STRAIGHT_BACKWARD;
//
//				break;
//
//			case LOCOM_STATE_TURN_LEFT:
//				locom_statRep.locomState = LOCOM_STATE_TURN_LEFT;
//
//				break;
//			case LOCOM_STATE_TURN_RIGHT:
//				locom_statRep.locomState = LOCOM_STATE_TURN_RIGHT;
//
//				break;
//
//			default:
//				//invalid command
//
//				break;
//
//		}
//	}
//}

//void pwm_enable(){
//
//	bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_ALT5);	//PWM function
//	bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_ALT5);	//PWM function
//
//	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
//	bcm2835_pwm_set_mode(0, 1, 1);	//set channel 0 to mark space mode?
//	bcm2835_pwm_set_mode(1, 1, 1);	//set channel 1 to mark space mode?
//	bcm2835_pwm_set_range(0, pwm_range);	//set resolution to 1024 bits
//	bcm2835_pwm_set_range(1, pwm_range);	//set resolution to 1024 bits
//
//	//set output of PWM to be 0 initially
//	//data = pwm_range (1024) would give pwm_range/pwm_range(100%), data = 0 gives 0/pwm_range (0%) and data = (pwm_range/2) gives  1/2 (50%)
//	bcm2835_pwm_set_data(0, 0);
//	bcm2835_pwm_set_data(1, 0);
//
//}

//void pwm_disable(){
//
//	bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_INPT);	//remove PWM function
//	bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_INPT);	//remove PWM function
//
//}

//void pwm_set_dc(int16_t m1_dc, int16_t m2_dc){
//
//	//pass % duty cycle between 0 and 100
//	//passing 1024 (PWM_RANGE) would give 100% dc, 512 50% and 0 0%
//	float dc;
//	dc = (float)pwm_range * (float)m1_dc/100.0;	//need to check the computation acts correctly
//	//right PWM (channel 0)
//	bcm2835_pwm_set_data(0, (int)dc);
//
//	//left PWM (channel 1)
//	dc = (float)pwm_range * (float)m2_dc/100.0;
//	bcm2835_pwm_set_data(1, (int)dc);
//
//
//}

//void locom_str_dur(int16_t power, int8_t direction){
//
//		printf("Setting a straight drive at %d power... \n", power);
//		//if power is greater
//		if (power > 0){
//			dig_set_direction(1,1);
//			pwm_set_dc(power, power);
//		}else if (power < 0){
//			dig_set_direction(0,0);
//			pwm_set_dc(power, power);
//
//		}
//
//
//}

//void locom_turn_dur(int16_t power, int16_t duration, int8_t direction){
//
//	printf("Starting a turn at %d power... \n", power);
//	//left = 0, right = 1
//	if (direction == 0){
//		//left
//		dig_set_direction(0,1);
//		pwm_set_dc(power, power);
//
//	}else if (direction == 1){
//		//right
//		dig_set_direction(1,0);
//		pwm_set_dc(power, power);
//
//	}
//	bcm2835_delay(duration);
//	//turn off the motors
//	pwm_set_dc(0, 0);
//
//
//}



