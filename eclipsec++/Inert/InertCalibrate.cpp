/*
 * InertCalibrate.cpp
 *
 *  Created on: 2 Mar 2018
 *      Author: G.P Team 1
 */

#include "InertModule.h"
#include <unistd.h>
int main()
{
	InertModule Inert = InertModule();

	Inert.Start();

	sleep(1);

	Inert.Calibrate();


}

