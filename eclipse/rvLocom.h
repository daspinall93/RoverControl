/*
 * rv_loc.h
 *
 *  Created on: 17 Jan 2018
 *      Author: dan
 */

#ifndef RVLOCOM_H_
#define RVLOCOM_H_


//#include <math.h>	//access math functions

#define PI 3.14159265

//definition of the different locomotion manoeuvres
#define LOCOM_COMMAND_STOP 0
#define LOCOM_COMMAND_STRAIGHT_FORWARD 1
#define LOCOM_COMMAND_STRAIGHT_BACKWARD 2
#define LOCOM_COMMAND_TURN_RIGHT 3
#define LOCOM_COMMAND_TURN_LEFT 4

//definition of the different states
#define LOCOM_STATE_STOP 0
#define LOCOM_STATE_STRAIGHT_FORWARD 1
#define LOCOM_STATE_STRAIGHT_BACKWARD 2
#define LOCOM_STATE_TURN_RIGHT 3
#define LOCOM_STATE_TURN_LEFT 4

//state of the wheels (forward, backward and stop)
#define LOCOM_WHEEL_FORWARD 1
#define LOCOM_WHEEL_BACKWARD 2
#define LOCOM_WHEEL_STOP 0

//structure definitions
//CAN BE ALTERED BY ANYONE
//structure containing the configuration of locomotion module
typedef struct {
	int pwmRange;	//range

} locom_modConfStruct;

//INPUT TO LOCOM, ONLY CHANGED BY CALLER (APART FROM NEWCOMMAND)
//structure containing the commands passed to the locomotion module
typedef struct {

	int power;	//power (0 to 100%)
	int msecDur;	//duration in msec
	uint8_t command;	//
	int8_t newCommand;	//boolean for if a new command has been produced

} locom_comConfStruct;
//OUTPUT OF LOCOM, CHANGED BY LOCOM
//structure containing the status as updated by the module provided to the calling module
typedef struct {

	uint8_t locomSubMode;
	long int comElapsedTimems;

} locom_statRepStruct;
//INTERNAL TO LOCOM, CHANGED BY LOCOM
typedef struct {

	long int comStartTimems;	//when the command started
	long int comElapsedTimems;		//how long command has been running for
	uint8_t locomSubMode; //current state of the module
	uint8_t locomRightWheel;	//current state of the right wheel
	uint8_t locomLeftWheel;	//current state of the left wheel
	//uint8_t locomNextState; //state to transition to next

} locom_internStateStruct;

//locmotion public functions
void locom_start();
void locom_do(locom_comConfStruct* p_locom_comConf, locom_statRepStruct* p_locom_statRep);
void locom_stop();

#endif /* RVLOCOM_H_ */
