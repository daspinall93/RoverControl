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

#include <string.h>

class ManagerModule
{
public:
	void Start(MotorModule* p_Motor_in, InertModule* p_Inert_in,
			SonarModule* p_Sonar_in, CommsModule* p_Comms_in, TelecModule* p_Telec_in);
	void Execute();
	void Stop();

private:
	/* OBJECTS TO CALL */
	MotorModule* p_Motor;
	InertModule* p_Inert;
	SonarModule* p_Sonar;
	CommsModule* p_Comms;
	TelecModule* p_Telec;

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

};

#endif /* MANAGER_MANAGERMODULE_H_ */
