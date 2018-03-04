/*
 * ManagerModule.h
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */

#ifndef MANAGER_MANAGERMODULE_H_
#define MANAGER_MANAGERMODULE_H_

/* INCLUDES FOR INTERACTING WITH MODULES */
#include "../Locom/LocomModule.h"
#include "../Comms/CommsModule.h"
#include "../Motor/MotorModule.h"
#include "../Local/LocalModule.h"
#include "../Inert/InertModule.h"
#include "../Camera/CameraModule.h"
#include "../Sonar/SonarModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"

#include <time.h>



class ManagerModule
{
public:
//	ManagerModule();
	void Start();
	void Execute();

private:
	/* OBJECTS TO CALL */
	LocomModule Locom;
//	CommsModule Comms;
	MotorModule Motor;
	LocalModule Local;
	InertModule Inert;
	SonarModule Sonar;
	CameraModule Camera;

	/* TIMING COMPONENTS */
	struct timespec tspec;	//used to retrieve the current time

	long int milSec;

	long int onehzHighMilSec;
	long int tenhzHighMilSec;

	uint8_t onehzFlag;
	uint8_t tenhzFlag;

	/* Structures for passing info between modules*/
	mavlink_locom_command_t LocomCommand;
	mavlink_locom_report_t LocomReport;

	mavlink_motor_command_t MotorCommand;
	mavlink_motor_report_t MotorReport;

	mavlink_local_command_t LocalCommand;
	mavlink_local_



	void StartTimer();
	void UpdateState();
	void DistributeCommands();
	void Debug();

};

#endif /* MANAGER_MANAGERMODULE_H_ */
