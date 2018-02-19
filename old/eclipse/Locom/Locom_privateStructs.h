/*
 * Locom_privateStructs.h
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

typedef struct {
	int pwmRange;	//range

} locom_modConfStruct;

typedef struct {

	long int comStartTimems;	//when the command started
	long int comElapsedTimems;		//how long command has been running for
	uint8_t locomSubMode; //current state of the module
	uint8_t locomRightWheel;	//current state of the right wheel
	uint8_t locomLeftWheel;	//current state of the left wheel
	//uint8_t locomNextState; //state to transition to next

} locom_internStateStruct;

