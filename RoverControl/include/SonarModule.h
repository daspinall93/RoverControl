/*
 * Sonar.h
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

#ifndef SONARMODULE_H_
#define SONARMODULE_H_

#include "mavlink/SoteriaRover/mavlink.h"

class SonarModule
{
public:

	void Start();
	void Execute(mavlink_sonar_command_t& SonarCommand_in,
			mavlink_sonar_report_t& SonarReport_out);
	void Stop();

	bool debugEnabled;

private:
	long int echoStartTime_us;
	long int echoEndTime_us;

	float distance_cm;


	short int objectDetectedFlag;
	/* 0 = echo pin wasnt low at beggining
	 * 1 = echo pin was low but never went high
	 * 2 = echo pin went high
	 * 3 = echo pin went high but didn't come low
	 * 4 = echo pin went high and came low
	 */

	void MeasureDistance();
	void UpdateReport(mavlink_sonar_report_t& SonarReport_out);
	void Debug();
};

#endif /* SONARMODULE_H_ */
