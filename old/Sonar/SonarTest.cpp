/*
 * SonarTest.cpp
 *
 *  Created on: 7 Mar 2018
 *      Author: dan
 */

#include "SonarModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include <bcm2835.h>

int main()
{
	if (!bcm2835_init())
		return 1;

	SonarModule Sonar;
	mavlink_sonar_command_t SonarCommand;
	mavlink_sonar_report_t SonarReport;

	Sonar.Start();

	Sonar.Execute(&SonarCommand, &SonarReport);
	bcm2835_close();

	return 0;

}


