/*
 * TimerContainer.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: AUser
 */

#include "TimerContainer.h"

void TimerContainer::Start()
{
	//set the initial time
	clock_gettime(CLOCK_MONOTONIC, &State.tspecInit);

	//set initial value of the time
	State.milSec = round(State.tspecInit.tv_nsec / 1.0e6);
	State.milSec = State.microSec + (State.tspecInit.tv_sec * 1000);

	State.prevMilSec = round(State.tspecInit.tv_nsec / 1.0e6);
	State.prevMilSec = State.prevMilSec + (State.tspecInit.tv_sec * 1000);
}

void TimerContainer::Execute()
{
	//when it starts update the times
	UpdateState();

	/* Update the flags to signify whether on this loop which functions are called */
	UpdateReport();

}

void TimerContainer::UpdateState()
{
	//update the times
	clock_gettime(CLOCK_MONOTONIC, &State.tspec);

	//set the previous time to the current time
	State.prevMilSec = State.milSec;

	//set the new time
	State.milSec = round(State.tspec.tv_nsec / 1.0e6);
	State.milSec = State.microSec + (State.tspecInit.tv_sec * 1000);
}

void TimerContainer::UpdateReport()
{
	//the difference in time between the last call and the current
	long int delta = State.milSec - State.prevMilSec;

	//turn on the flag if 100ms have passed since the last call
	if (delta > 100)
	{
		Report.onehzFlag = 1;
	}
	else
	{
		Report.onehzFlag = 0;
	}

	//turn on the flag if 10ms have passed since the last call
	if (delta < 10)
	{
		Report.tenhzFlag = 1;
	}
	else
	{
		Report.tenhzFlag = 0;
	}

}
