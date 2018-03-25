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

	// Parse input arguments for port and target IP (ground)
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

	ManagerModule Manager = ManagerModule();

	Manager.Start(atoi(argv[2]), argv[1]);

	Manager.Execute();

	Manager.Stop();

	return 0;

}
