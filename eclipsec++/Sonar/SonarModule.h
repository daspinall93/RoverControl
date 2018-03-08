/*
 * Sonar.h
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

#ifndef SONARMODULE_H_
#define SONARMODULE_H_

#include "../mavlink/SoteriaRover/mavlink.h"

class SonarModule
{
public:

	void Start();
	void Execute(mavlink_sonar_command_t* p_SonarCommand_in,
			mavlink_sonar_report_t* p_SonarReport_out);
	void Stop();

private:
	long int echoStartTime_us;
	long int echoEndTime_us;

	float distance_cm;

	uint8_t objectDetectedFlag;

	void MeasureDistance();
	void UpdateReport(mavlink_sonar_report_t* p_SonarReport_out);
	void Debug();
};

#endif /* SONARMODULE_H_ */
