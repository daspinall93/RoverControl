/*
 * ManagerTest.cpp
 *
 *  Created on: 6 Mar 2018
 *      Author: dan
 */
#include "ManagerModule.h"
#include <string.h>

int main()
{
	ManagerModule Manager = ManagerModule();

	Manager.Start();

	Manager.Execute();

	Manager.Stop();

}



