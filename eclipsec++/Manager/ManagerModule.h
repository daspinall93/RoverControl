/*
 * ManagerModule.h
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */

#ifndef MANAGER_MANAGERMODULE_H_
#define MANAGER_MANAGERMODULE_H_


/* INCLUDES FOR INTERACTING WITH MODULES */
#include "../Motor/MotorModule.h"
#include "../Inert/InertModule.h"
#include "../Camera/CameraModule.h"
#include "../Sonar/SonarModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"

#include <string.h>


class ManagerModule
{
public:

	void Start();
	void Execute();
	void Stop();

private:
	/* OBJECTS TO CALL */
	MotorModule Motor;
	InertModule Inert;
	SonarModule Sonar;
	CameraModule Camera;

	/* TIMING COMPONENTS */


	long int milSec;

	long int onehzHighMilSec;
	long int tenhzHighMilSec;

	uint8_t onehzFlag;
	uint8_t tenhzFlag;

	uint8_t endProgram_flag;
	/* Structures for passing info between modules*/
	mavlink_motor_command_t MotorCommand;
	mavlink_motor_report_t MotorReport;

	mavlink_inert_report_t InertReport;
	mavlink_inert_command_t InertCommand;

	mavlink_sonar_command_t SonarCommand;
	mavlink_sonar_report_t SonarReport;

	mavlink_camera_command_t CameraCommand;

	void StartTimer();
	void UpdateTimer();
	void GetCmdLineInput();
	void ExecuteCommand();
	void Debug();

};

#endif /* MANAGER_MANAGERMODULE_H_ */
