/*
 * ManagerModule.cpp
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */

#include "ManagerModule.h"

/* INCLUDES FOR TIMING PURPOSES */
#include <math.h>
#include <bcm2835.h>
#include <time.h>

/* INCLUDED FOR THE COMMAND INTERPRITATION FUNCTION */
#include "../mavlink/SoteriaRover/mavlink.h"

/* INCLUDES FOR THREADING TO GET INPUT FROM CMD LINE */
#include <iostream>
#include <stdio.h>
#include <string.h>

/* SELECT WHICH ELEMENTS WILL BE ENABLED */
#define MOTOR_ENABLED 1
#define INERT_ENABLED 1
#define SONAR_ENABLED 1
#define CAMERA_ENABLED 1

void ManagerModule::Start()
{
    /* NEED TO ENBALE BCM2835 LIBRARY FOR USING PI PINS */
#if MOTORS_ENABLED || INERT_ENABLED
    bcm2835_init();
#endif

#if INERT_ENABLED
    Inert.Start();
#endif

#if MOTOR_ENABLED
    Motor.Start();
#endif

#if SONAR_ENABLED
    Sonar.Start();
#endif

#if CAMERA_ENABLED
    Camera.Start();
#endif
    /* START THE ROVER MODULES TIMER */
    StartTimer();
}

void ManagerModule::Execute()
{
    while (1)
    {
		/* UPDATE TIMER FLAGS */
    	UpdateTimer();

    	/* CARRY OUT CYCLIC TASKS */
		/* EXECUTE MODULES AT 1HZ */
		if (onehzFlag)
		{

		}

		/* EXECUTE MODULES AT 10HZ */
		if (tenhzFlag)
		{
			/* POLL COMMAND LINE TO SEE IF NEW COMMAND HAS BEEN RECEIVED */


#if INERT_ENABLED
			/* GET REPORT FROM INERT MODULE FOR COARSE TILT */
			Inert.Execute(&InertReport);
#endif
		}
    }
}

void ManagerModule::StartTimer()
{
	struct timespec tspec;	//used to retrieve the current time

    /* SET TIME AT WHICH THE ROVER STARTED */
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    milSec = round(tspec.tv_nsec / 1.0e6);
    milSec = milSec + (tspec.tv_sec * 1000);

    /* SET THE REFERENCE TIMES */
    tenhzHighMilSec = milSec;
    onehzHighMilSec = milSec;

    /* START FLAGS HIGH */
    onehzFlag = 1;
    tenhzFlag = 1;

}

void ManagerModule::UpdateTimer()
{
	struct timespec tspec;	//used to retrieve the current time

    /* IF HIGH RESET */
    if (onehzFlag)
    {
    	onehzFlag = 0;
    }

    if (tenhzFlag)
    {
    	tenhzFlag = 0;
    }

    /* UPDATE THE TIME */
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    milSec = round(tspec.tv_nsec / 1.0e6);
    milSec = milSec + (tspec.tv_sec * 1000);

    /* SEE IF 10MS HAS PASSED SINCE LAST TIME TENHZ FLAG WAS HIGH */
    long int delta = milSec - tenhzHighMilSec;
    if (delta > 100)
    {
		/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
		tenhzFlag = 1;
		tenhzHighMilSec = milSec;
    }

    /* SEE IF 100MS HAS PASSED SINCE LAST TIME ONEHZ FLAG WAS HIGH */
    delta = milSec - onehzHighMilSec;
    if (delta > 1000)
    {
		/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
		onehzFlag = 1;
		onehzHighMilSec = milSec;
    }

}

void ManagerModule::GetCmdLineInput()
{
	char mystring[100];
	std::string s;
	std::string delimiter = " ";
	size_t pos = 0;

	std::string token;

	/* POLL THE CMD LINE TO SEE IF ANY INPUT WAS PRESENT */
	if (fgets(mystring, 100, stdin) != NULL)
	{
		cmdLineInput = mystring;

		/* GO THROUGH EACH ELEMENT OF THE COMMAND */
		while ((pos = s.find(delimiter)) != std::string::npos) {
		    token = s.substr(0, pos);
		    std::cout << token << std::endl;
		    s.erase(0, pos + delimiter.length());
		}

	}



}
void ManagerModule::Debug()
{



}



