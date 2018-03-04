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

	Manager.Start();

	Manager.Execute();

	return 0;

}
