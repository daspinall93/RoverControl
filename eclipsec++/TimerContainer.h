/*
 * TimerContainer.h
 * Container to maintain the time and set 10hz and 100hz flags for the scheduler
 * to use
 *  Created on: 14 Feb 2018
 *      Author: AUser
 */

#ifndef TIMERCONTAINER_H_
#define TIMERCONTAINER_H_

#include <time.h>
#include <math.h>

class TimerContainer
{
public:

	struct
	{
		uint8_t onehzFlag;	//flag signifying
		uint8_t tenhzFlag;
		//uint8_t 100hzFlag;
	} Report;

	struct
	{

	} Parameters;

	TimerContainer(){};
	void Start();
	void Execute();

private:

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

	void UpdateState();
	void UpdateReport();

protected:

};


#endif /* TIMERCONTAINER_H_ */
