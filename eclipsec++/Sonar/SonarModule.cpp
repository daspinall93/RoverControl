/*
 * Sonar.cpp
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

#include <bcm2835>
#include "../Utils/Utils.h"

/* DEFINE GPIO PIN NUMBERING */
#define TRIG_GPIO 5
#define ECHO_GPIO 6

SonarModule::SonarModule()
{
	/* INITIALISE ALL DATA TO 0 */
    memset(&Report, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Report));
    memset(&State, 0, sizeof(Report));
    memset(&Command, 0, sizeof(Report));

}

void SonarModule::Start()
{

	/* SETUP CONFIG */
	Config.echoPin = ECHO_GPIO;
	Config.trigPin = TRIG_GPIO;

	/* SETUP THE PINS */
    bcm2835_gpio_fsel(Config.echoPin , BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(Config.trigPin, BCM2835_GPIO_FSEL_OUTP);

    /* ENSURE TRIGGER PIN IS LOW */
    bcm2835_gpio_write(Config.trigPin, LOW);
}

void SonarModule::Execute()
{
	/* IF NEW COMMAND HAS BEEN PASSED TAKE MEASUREMENT */
	if (Command.makeNewMeasurement)
	{
		/* MEASURE THE TIME BETWEEN PULSE AND ECHO */
		MeasureEcho();
	}

	UpdateReport();

}

void SonarModule::MeasureEcho()
{
	/* SET THE TRIGGER */
	bcm2835_gpio_write(Config.trigPin, HIGH);

	/* WAIT FOR THE ECHO PIN TO GO HIGH */
	/* TODO ADD ERROR CHECKING FOR IF THE PIN NEVER GOES HIGH/COMES LOW */
	while (!bcm2835_gpio_lev(Config.echoPin))
	{
		State.echoStartTime_us = Utils::GetTimeus();
	}

	/* MEASURE HOW LONG THE ECHO PIN IS HIGH FOR */
	while (bcm2835_gpio_lev(Config.echoPin))
	{
		State.echoEndTime_us= Utils::GetTimeus();
	}

	State.newMeasure = 1;

}

void SonarModule::UpdateReport()
{
	/* UPDATE REPORT DEPENDING ON IF NEW MEASURE HAS BEEN MADE */
	if (State.newMeasure)
	{
		/* MEASURE THE NEW DELTA TIME */
		Report.newMeasureUpdate = 1;
		Report.echoHighTime_us = State.echoEndTime_us - State.echoEndTime_us;
	}
	else
	{
		/* NO NEW UPDATE TO THE SONAR MEASUREMENT */
		Report.newMeasureUpdate = 0;
	}
}
