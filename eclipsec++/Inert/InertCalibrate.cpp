/*
 * InertCalibrate.cpp
 *
 *  Created on: 2 Mar 2018
 *      Author: G.P Team 1
 */

#include "InertModule.h"
#include <unistd.h>
#include <bcm2835.h>

int main()
{
	bcm2835_init();

	InertModule Inert = InertModule();

	Inert.Start();

	sleep(1);

	Inert.CalibrateMPU();


}

