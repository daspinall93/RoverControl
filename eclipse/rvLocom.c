/*
 * rv_loc.c
 *
 *  Created on: 17 Jan 2018
 *      Author: dan
 */

#include <math.h>
#include <stdio.h>
#include "bcm2835.h"	//interface with motors
#include "rvLocom.h"
#include "rvUtils.h"	//helpful self-contained functions

//pin defintions
//drive pins
#define ENA 18	//PWM
#define ENB 19	//PWM
//M1=right motor
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
//M2 = left motor
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2

//private data for locom to access
locom_internStateStruct locom_internState;
locom_modConfStruct locom_modConf;

//private functions
void locom_subModeAction();
void locom_genStatRep(locom_statRepStruct* p_locom_statRep);
void locom_subModeTransition(locom_comConfStruct* p_locom_comConf);

void locom_start(){

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

void locom_do(locom_comConfStruct* p_locom_comConf, locom_statRepStruct* p_locom_statRep){

	//print out state of the module
	printf("[LOCOM ENTRY]right wheel = %d \t left wheel = %d \n", locom_internState.locomLeftWheel, locom_internState.locomRightWheel);


	//carry out state transition if new command received
	locom_subModeTransition(p_locom_comConf);

	//carry out actions depending on new state
	locom_subModeAction();

	//generate the status report
	locom_genStatRep(p_locom_statRep);

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

void locom_subModeTransition(locom_comConfStruct* p_locom_comConf){
	//carry out the state transitions and change the output
	//depending on the command, change output to motors and state appropriately

	if (p_locom_comConf->newCommand){
		switch(p_locom_comConf->command){

			case LOCOM_COMMAND_STOP:
				//stay in standby

				locom_internState.locomSubMode = LOCOM_STATE_STOP;
				locom_internState.locomLeftWheel = LOCOM_WHEEL_STOP;
				locom_internState.locomRightWheel = LOCOM_WHEEL_STOP;
				break;

			case LOCOM_COMMAND_STRAIGHT_FORWARD:
				//drive straight command

				//set to drive all wheels forward
				locom_internState.locomSubMode = LOCOM_STATE_STRAIGHT_FORWARD;
				locom_internState.locomLeftWheel = LOCOM_WHEEL_FORWARD;
				locom_internState.locomRightWheel = LOCOM_WHEEL_FORWARD;
				break;

			case LOCOM_COMMAND_STRAIGHT_BACKWARD:
				//go in a straight line backwards

				//set to drive all wheels backward
				locom_internState.locomSubMode = LOCOM_STATE_STRAIGHT_BACKWARD;
				locom_internState.locomLeftWheel = LOCOM_WHEEL_BACKWARD;
				locom_internState.locomRightWheel = LOCOM_WHEEL_BACKWARD;
				break;

			case LOCOM_COMMAND_TURN_LEFT:
				//turn left command

				//set to drive left wheels back and right forward
				locom_internState.locomSubMode = LOCOM_STATE_TURN_LEFT;
				locom_internState.locomLeftWheel = LOCOM_WHEEL_STOP;
				locom_internState.locomRightWheel = LOCOM_WHEEL_FORWARD;
				break;
			case LOCOM_COMMAND_TURN_RIGHT:
				//turn right command

				//set to drive left wheels forward and right backward
				locom_internState.locomSubMode = LOCOM_STATE_TURN_RIGHT;
				locom_internState.locomLeftWheel = LOCOM_WHEEL_FORWARD;
				locom_internState.locomRightWheel = LOCOM_WHEEL_STOP;
				break;

			default:
				//invalid command

				break;

		}

		//set the time at which the command started
		locom_internState.comStartTimems = utils_getTimems();
		locom_internState.comElapsedTimems = 0;
		p_locom_comConf->newCommand = 0;	//set to 0 as new command has been processed

	}else{

		//no new command so need to check time elapsed
		locom_internState.comElapsedTimems = (utils_getTimems() - locom_internState.comStartTimems);
		if(locom_internState.comElapsedTimems >= p_locom_comConf->msecDur){
			//the command has ended so turn of motors and set appropriate

			locom_internState.locomSubMode = LOCOM_STATE_STOP;
			locom_internState.locomLeftWheel = LOCOM_WHEEL_STOP;
			locom_internState.locomRightWheel = LOCOM_WHEEL_STOP;
			locom_internState.comElapsedTimems = 0;

		}

	}

}

void locom_genStatRep(locom_statRepStruct* p_locom_statRep){

	//generate the latest state report
	p_locom_statRep->locomSubMode = locom_internState.locomSubMode;
	p_locom_statRep->comElapsedTimems = locom_internState.comElapsedTimems;

}

void locom_subModeAction(){

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



