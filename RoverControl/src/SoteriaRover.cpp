/*
 * SoteriaRover.cpp
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */
#include "ManagerModule.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{

	/* PARSE INPUT TO GET THE PORT NUMBER AND IP ADDRESS */
	if (argc < 3)
	{
		std::cout << "Not enough input arguments" << std::endl;
		return 1;
	}
	else if (argc > 3)
	{
		std::cout << "Too many input arguments" << std::endl;
		return 1;
	}

	/* CONVERT THE PORT NUMBER TO AN INT */

	TelecModule Telec = TelecModule();
	ManagerModule Manager = ManagerModule();
	MotorModule Motor = MotorModule();
	InertModule Inert = InertModule();
	SonarModule Sonar = SonarModule();
	CommsModule Comms = CommsModule(atoi(argv[2]), argv[1]);


	Manager.Start(&Motor, &Inert, &Sonar, &Comms, &Telec);

	Manager.Execute();

	Manager.Stop();

	return 0;

}
