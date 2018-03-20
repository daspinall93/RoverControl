/*
 * Sonar.cpp
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */
#include "SonarModule.h"
#include <bcm2835.h>
#include "../Utils/Utils.h"
#include <iostream>

/* DEFINE GPIO PIN NUMBERING */
#define TRIG_PIN 5
#define ECHO_PIN 6

/* ECHO TIMEOUT TO ENSURE THE PROGRAM ISN'T STOPPED IF NO RESPONSE IS RECEIVED */
#define ECHO_TIMEOUT_US 5000000

/* VALUE FOR CONVERTING TIME TO DISTANCE */
#define CONVERSION_FACTOR_CM 0.017

void SonarModule::Start()
{
	std::cout << "[SONAR]Starting Module..." << std::endl;

	/* SETUP THE PINS */
    bcm2835_gpio_fsel(ECHO_PIN , BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_PIN, BCM2835_GPIO_FSEL_OUTP);

    /* ENSURE TRIGGER PIN IS LOW */
    bcm2835_gpio_write(TRIG_PIN, LOW);

    objectDetectedFlag = 0;

}

void SonarModule::Execute(mavlink_sonar_command_t* p_SonarCommand_in,
		mavlink_sonar_report_t* p_SonarReport_out)
{
	/* MEASURE THE TIME BETWEEN PULSE AND ECHO */
	MeasureDistance();

	UpdateReport(p_SonarReport_out);

	Debug();

}

void SonarModule::Stop()
{
    bcm2835_gpio_write(TRIG_PIN, LOW);

    bcm2835_gpio_fsel(ECHO_PIN , BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(TRIG_PIN, BCM2835_GPIO_FSEL_INPT);

}
void SonarModule::MeasureDistance()
{
	/* START TIMEOUT TIMER */
	long int startTime_us = Utils::GetTimeus();

	/* SET FLAG TO LOW */
	objectDetectedFlag = 0;

	/* SET THE TRIGGER */
	bcm2835_gpio_write(TRIG_PIN, HIGH);
	bcm2835_delayMicroseconds(10);
	bcm2835_gpio_write(TRIG_PIN, LOW);
	echoStartTime_us = Utils::GetTimeus();

	/* WAIT FOR ECHO PIN TO GO HIGH */
	while (!bcm2835_gpio_lev(ECHO_PIN))
	{
		echoStartTime_us = Utils::GetTimeus();
		objectDetectedFlag = 2;

		/* BREAK FROM LOOP IF TIMEOUT IS REACHED AND SET DETECTED FLAG LOW */
		if ((echoStartTime_us - startTime_us) >= ECHO_TIMEOUT_US)
		{
			objectDetectedFlag = 1;
			break;

		}
	}

	/* ONLY CHECK FOR PIN GOING LOW IF IT WENT HIGH IN FIRST PLACE */
	if (objectDetectedFlag == 2)
	{
		/* MEASURE HOW LONG THE ECHO PIN IS HIGH FOR */
		while (bcm2835_gpio_lev(ECHO_PIN))
		{
			objectDetectedFlag = 4;
			echoEndTime_us= Utils::GetTimeus();

			/* BREAK FROM LOOP IF TIMEOUT IS REACHED AND SET DETECTED FLAG LOW */
			if ((echoEndTime_us - echoStartTime_us) >= ECHO_TIMEOUT_US)
			{
				objectDetectedFlag = 3;
				break;

			}

		}
	}

	/* IF A VALID TIME WAS RECEIVED THEN CALCULATE DISTANCE */
	if (objectDetectedFlag == 4)
	{
		/* ASSUME AS OBJECT HAS BEEN DETECTED THAT TIME WONT BE 0 */
		long int delta_time_us = echoStartTime_us - echoEndTime_us;
		distance_cm = std::abs(delta_time_us * CONVERSION_FACTOR_CM);

	}
	else
	{
		distance_cm = 0;
	}

}

void SonarModule::UpdateReport(mavlink_sonar_report_t* p_SonarReport_out)
{
	/* UPDATE REPORT DEPENDING ON IF NEW MEASURE HAS BEEN MADE */
	p_SonarReport_out->objectDetected_flag = objectDetectedFlag;
	p_SonarReport_out->objectDistance_cm = distance_cm;

}

void SonarModule::Debug()
{
	std::cout << "[SONAR]Object detected flag = " << objectDetectedFlag << std::endl;
	std::cout << "[SONAR]Object Distance = " << distance_cm << std::endl;

}
