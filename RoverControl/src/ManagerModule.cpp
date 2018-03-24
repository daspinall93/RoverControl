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

/* INCLUDES FOR THREADING TO GET INPUT FROM CMD LINE */
#include <iostream>
#include <stdio.h>
#include <string.h>

/* FOR CONSTANT PWM */
#define PWM_PERCENTAGE 70

void ManagerModule::Start(MotorModule* p_Motor_in, InertModule* p_Inert_in,
		SonarModule* p_Sonar_in, CommsModule* p_Comms_in,
		TelecModule* p_Telec_in, TelemModule* p_Telem_in)
{
	/* ASSIGN OBJECT POINTERS */
	p_Motor = p_Motor_in;
	p_Inert = p_Inert_in;
	p_Sonar = p_Sonar_in;
	p_Comms = p_Comms_in;
	p_Telec = p_Telec_in;
	p_Telem = p_Telem_in;

	/* NEED TO ENBALE BCM2835 LIBRARY FOR USING PI PINS */
	bcm2835_init();

	p_Inert->Start();

	p_Motor->Start();

	p_Sonar->Start();

	p_Comms->Start();

	p_Telec->Start();

	p_Telem->Start();

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
			// Check to see if any messages have been received and send messages
			PrepComms(&CommsCommand, &TelemReport);
			p_Comms->Execute(&CommsCommand, &CommsReport);

			// Pass the comms report to parse any commands received
			PrepTelec();
			p_Telec->Execute(&TelecReport, &CommsReport);

			// Pass the commands from telex report to modules
			p_Motor->Execute(&TelecReport.MotorCommand, &MotorReport);
			TelecReport.MotorCommand.newCommand = 0; // Set new command flag to 0

			p_Inert->Execute(&InertReport);
			TelecReport.InertCommand.newCommand = 0; // Set new command flag to 0

			// Run the Telem module to send data back to GS
			TelemCommand.InertReport = InertReport;
			TelemCommand.MotorReport = MotorReport;
			TelemCommand.SonarReport = SonarReport;
			p_Telem->Execute(&TelemCommand, &TelemReport);

		}
		if (onehzFlag)
		{
			p_Sonar->Execute(&TelecReport.SonarCommand, &SonarReport);
			TelecReport.SonarCommand.newCommand = 0; // Set new command flag to 0
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

void ManagerModule::PrepComms(mavlink_comms_command_t* p_CommsCommand,
		const mavlink_telem_report_t* p_TelemReport)
{
	CommsCommand.BufferLength = TelemReport.bufferLength;
	memcpy(CommsCommand.msgSendBuffer, TelemReport.buffer,
			TelemReport.bufferLength);
}

void ManagerModule::PrepTelec(mavlink_telec_command_t* p_TelecCommand,
		const mavlink_telem_report_t* p_CommsReport)
{

}
void ManagerModule::Debug()
{

}

