/*
 * InertTest.cpp
 *
 *  Created on: 26 Feb 2018
 *      Author: G.P Team 1
 */

#include <bcm2835.h>
#include "../mavlink/SoteriaRover/mavlink.h"
#include "InertModule.h"

#include <unistd.h>

int main()
{
	InertModule Inert = InertModule();
	mavlink_inert_report_t InertReport;

	/* INITIALISE THE BCM LIBRARY */
	bcm2835_init();

	/* CALL START AND THEN GET REPORT AND CHECK REPORT */
	Inert.Start();

	/* ENSURE IMU IS GIVEN TIME TO SWITCH ON */
	bcm2835_delay(100);

	/* EXECUTE INERT TO UPDATE MEASUREMENTS at 10HZ */
	for (int i = 0; i < 100; i++)
	{
		Inert.Execute(&InertReport);
		bcm2835_delay(100);
	}

	bcm2835_close();
}

