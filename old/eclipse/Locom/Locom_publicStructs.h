/*
 * Locom_internState.h
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

#ifndef LOCOM_LOCOM_PUBLICSTRUCTS_H_
#define LOCOM_LOCOM_PUBLICSTRUCTS_H_

/* COMMAND STRUCTURE FOR LOCOM */
typedef struct {

	int power;	//power (0 to 100%)
	int msecDur;	//duration in msec
	uint8_t command;	//
	int8_t newCommand;	//boolean for if a new command has been produced

} locom_comConfStruct;

/* REPORT STRUCTURE FOR LOCOM */
typedef struct {

	uint8_t locomSubMode;
	long int comElapsedTimems;

} locom_statRepStruct;

#endif /* LOCOM_LOCOM_PUBLICSTRUCTS_H_ */
