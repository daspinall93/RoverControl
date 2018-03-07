/*
 * SoteriaRover.cpp
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */
#include "Manager/ManagerModule.h"

int main()
{

	ManagerModule Manager = ManagerModule();
	MotorModule Motor = MotorModule();
	InertModule Inert = InertModule();
	SonarModule Sonar = SonarModule();
	CameraModule Camera = CameraModule();

	Manager.Start(&Motor, &Inert, &Sonar, &Camera);

	Manager.Execute();

	Manager.Stop();

	return 0;

}
