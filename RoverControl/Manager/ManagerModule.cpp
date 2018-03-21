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
//#include "../mavlink/SoteriaRover/mavlink.h"

/* INCLUDES FOR THREADING TO GET INPUT FROM CMD LINE */
#include <iostream>
#include <stdio.h>
#include <string.h>

/* FOR CONSTANT PWM */
#define PWM_PERCENTAGE 70

void ManagerModule::Start(MotorModule* p_Motor_in, InertModule* p_Inert_in,
		SonarModule* p_Sonar_in, CommsModule* p_Comms_in, TelecModule* p_Telec_in)
{
	/* ASSIGN OBJECT POINTERS */
	p_Motor = p_Motor_in;
	p_Inert = p_Inert_in;
	p_Sonar = p_Sonar_in;
	p_Comms = p_Comms_in;
	p_Telec = p_Telec_in;

    /* NEED TO ENBALE BCM2835 LIBRARY FOR USING PI PINS */
    bcm2835_init();

//    p_Comms->Start();

    p_Inert->Start();

    p_Motor->Start();

    p_Sonar->Start();

    p_Comms->Start();

    p_Telec-> Start();

    /* START THE ROVER MODULES TIMER */
    StartTimer();

}

void ManagerModule::Execute()
{
	/* INITIATE THREAD THAT WILL WATCH FOR INPUT ON THE CMD LINE */

    while (!endProgram_flag)
    {
		/* UPDATE TIMER FLAGS */
    	UpdateTimer();

    	if (tenhzFlag)
    	{
    		/* RUN TELEM TO UPDATE THE COMMS COMMAND */

    		/* CHECK COMMS MODULE */
    		p_Comms->Execute(&CommsCommand, &CommsReport);

    		/* RUN TELEC TO SEE IF COMMAND HAS BEEN ISSUED */
    		//p_Telec->Execute(&TelecReport, &CommsReport);


    	}

    	/* DELAY TO STOP FROM RUNNING TOO QUICKLY */
    	bcm2835_delay(10);

	    /* CHECK FOR COMMAND INPUT */
	    //GetCmdLineInput();

	    /* EXECUTE ANY COMMANDS */
	    //ExecuteCommand();

    	Debug();

    }

}

void ManagerModule::Stop()
{

    p_Inert->Stop();

    p_Motor->Stop();

    p_Sonar->Stop();

    bcm2835_close();
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
	std::string cmdLineInput;
	size_t pos = 0;

	std::string token;

	/* POLL THE CMD LINE TO SEE IF ANY INPUT WAS PRESENT */
	std::cout << ">>";
	std::cin >> cmdLineInput;

	/* GO THROUGH EACH ELEMENT OF THE COMMAND */
	if ((pos = cmdLineInput.find(" ")) != std::string::npos)
	{
		std::cout << "Only one value allowed" << std::endl;
	}
	else
	{
		token = cmdLineInput.substr(0, pos);

		if (token == "forward")
		{
			/* CURRENTLY ONLY USING THE FORWARD COMMAND WITH NO TIME OR POWER INPUT */
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STRAIGHT_FORWARD;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "backward")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STRAIGHT_BACKWARD;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "right")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_TURN_RIGHT;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "left")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_TURN_LEFT;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "stop")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STOP;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "tilt")
		{
			InertCommand.newCommand = 1;
		}
		else if (token == "distance")
		{
			SonarCommand.newCommand = 1;
		}
		else if (token == "end")
		{
			endProgram_flag = 1;
		}
		else
		{
			std::cout << "Incorrect Command" << std::endl;
		}
	}
}

void ManagerModule::ExecuteCommand()
{
    /* CHECK TO SEE IF A NEW COMMAND HAS BEEN ASSIGNED FOR ANY MODULE */
    if (MotorCommand.newCommand)
    {
    	p_Motor->Execute(&MotorCommand, &MotorReport);
    	MotorCommand.newCommand = 0;
    }
    if (InertCommand.newCommand)
    {
    	p_Inert->Execute(&InertReport);
    	InertCommand.newCommand = 0;
    }
    if (SonarCommand.newCommand)
    {
    	p_Sonar->Execute(&SonarCommand, &SonarReport);
    	SonarCommand.newCommand = 0;
    }
}

void ManagerModule::Debug()
{

}



