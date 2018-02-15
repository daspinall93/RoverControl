/*
 * TimerModule.h
 * Container to maintain the time and set 10hz and 100hz flags for the scheduler
 * to use
 *  Created on: 14 Feb 2018
 *      Author: AUser
 */

#ifndef TIMERMODULE_H_
#define TIMERMODULE_H_

#include "LocomModule.h"
#include "MotorModule.h"
#include "CommsModule.h"
#include <time.h>
#include <math.h>

class TimerModule
{
public:
	struct
	{
		//flags for timings
		uint8_t onehzFlag;
		uint8_t tenhzFlag;
		//uint8_t 100hzFlag;
	} Report;

	struct
	{

	} Config;

	TimerModule(){};
	void Start();
	void Execute();

	//used for allowing calls to start and execute members
	friend LocomModule Locom;
	friend MotorModule Motors;
	friend CommsModule Comms;


	/* PRIVATE DATA MEMBER */
	struct
	{
		struct timespec tspecInit;	//time at which the timer was started
		struct timespec tspec;	//used to retrieve the current time

		//current time
		long int milSec;
		long int microSec;

		//previous time used to check if flag should be high or low
		long int prevMilSec;
		long int prevMicroSec;
	} State;

	/* PRIVATE FUNCTIONS MEMBERS */
	void UpdateState();
	void UpdateReport();

};


#endif /* TIMERMODULE_H_ */
