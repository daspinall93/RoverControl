/*
 * ManagerModule.h
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */

#ifndef MANAGER_MANAGERMODULE_H_
#define MANAGER_MANAGERMODULE_H_

/* INCLUDES FOR INTERACTING WITH MODULES */
#include "MotorModule.h"
#include "InertModule.h"
#include "SonarModule.h"
#include "CommsModule.h"
#include "CommsInterfaceStructs.h"
#include "mavlink/SoteriaRover/mavlink.h"
#include "TelecModule.h"
#include "TelecInterfaceStructs.h"
#include "TelemInterfaceStructs.h"
#include "TelemModule.h"

#include <string.h>
#include <stdint.h>
class ManagerModule
{
public:
	void Start(MotorModule* p_Motor_in, InertModule* p_Inert_in,
			SonarModule* p_Sonar_in, CommsModule* p_Comms_in,
			TelecModule* p_Telec_in, TelemModule* p_Telem_in);
	void Execute();
	void Stop();

private:
	/* OBJECTS TO CALL */
	MotorModule* p_Motor;
	InertModule* p_Inert;
	SonarModule* p_Sonar;
	CommsModule* p_Comms;
	TelecModule* p_Telec;
	TelemModule* p_Telem;

	/* TIMING COMPONENTS */

	long int milSec;

	long int onehzHighMilSec;
	long int tenhzHighMilSec;

	uint8_t onehzFlag;
	uint8_t tenhzFlag;

	uint8_t endProgram_flag;

	/* Structures for passing info between modules*/
	mavlink_comms_command_t CommsCommand;
	mavlink_comms_report_t CommsReport;

	mavlink_telec_report_t TelecReport;
	mavlink_telec_command_t TelecCommand;

	mavlink_telem_report_t TelemReport;
	mavlink_telem_command_t TelemCommand;

	mavlink_motor_command_t MotorCommand;
	mavlink_motor_report_t MotorReport;

	mavlink_inert_report_t InertReport;
	mavlink_inert_command_t InertCommand;

	mavlink_sonar_command_t SonarCommand;
	mavlink_sonar_report_t SonarReport;

	void StartTimer();
	void UpdateTimer();
	void GetCmdLineInput();
	void ExecuteCommand();
	void Debug();

	// Functions for preparing input to modules
	void PrepComms(mavlink_comms_command_t* p_CommsCommand,
			const mavlink_telem_report_t* p_TelemReport);

	void PrepTelec(mavlink_telec_command_t* p_TelecCommand,
			const mavlink_telem_report_t* p_CommsReport);

};

#endif /* MANAGER_MANAGERMODULE_H_ */
