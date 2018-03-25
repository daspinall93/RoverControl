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

void ManagerModule::Start(int port, char* ip)
{
	// Enable the bcm library for pin access
	bcm2835_init();

	// Start the modules
	Inert.Start();

	Motor.Start();

	Sonar.Start();

	Comms.Start(port, ip);

	Telec.Start();

	Telem.Start();

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
			PrepComms(CommsCommand, TelemReport);
			Comms.Execute(CommsCommand, CommsReport);

			// Pass the comms report to parse any commands received
			PrepTelec(TelecCommand, CommsReport);
			Telec.Execute(TelecReport, TelecCommand);

			// Pass the commands from telec report to modules
			Motor.Execute(TelecReport.MotorCommand, MotorReport);
			TelecReport.MotorCommand.newCommand = 0; // Set new command flag to 0

			Inert.Execute(InertReport);
			TelecReport.InertCommand.newCommand = 0; // Set new command flag to 0

			// Run the Telem module to send data back to GS
			PrepTelem(TelemCommand, MotorReport, SonarReport, InertReport);
			Telem.Execute(TelemCommand, TelemReport);

		}
		if (onehzFlag)
		{

			Sonar.Execute(TelecReport.SonarCommand, SonarReport);
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

	Inert.Stop();

	Motor.Stop();

	Sonar.Stop();

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

void ManagerModule::PrepComms(mavlink_comms_command_t& CommsCommand,
		const mavlink_telem_report_t& TelemReport)
{
	// Copy the buffer content from the telem output to the comms input
	CommsCommand.bufferLength = TelemReport.bufferLength;
	memcpy(CommsCommand.msgSendBuffer, TelemReport.buffer,
			TelemReport.bufferLength);
}

void ManagerModule::PrepTelec(mavlink_telec_command_t& TelecCommand,
		const mavlink_comms_report_t& CommsReport)
{
	// Take the buffer produced by comms and pass to Telec input
	TelecCommand.bufferLength = CommsReport.numBytesRec;
	memcpy(TelecCommand.buffer, CommsReport.msgRecBuffer,
			CommsReport.numBytesRec);

}

void ManagerModule::PrepTelem(mavlink_telem_command_t& TelemCommand,
		const mavlink_motor_report_t& MotorReport,
		const mavlink_sonar_report_t& SonarReport,
		const mavlink_inert_report_t& InertReport)
{
	// put all the reports from the modules in the telem input
	TelemCommand.InertReport = InertReport;
	TelemCommand.MotorReport = MotorReport;
	TelemCommand.SonarReport = SonarReport;
}
void ManagerModule::Debug()
{

}

