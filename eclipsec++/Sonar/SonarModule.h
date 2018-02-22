/*
 * Sonar.h
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

#ifndef SONARMODULE_H_
#define SONARMODULE_H_

class SonarModule
{
public:
	struct
	{
		uint8_t newMeasureUpdate;
		long int echoHighTime_us;

	} Report;

	struct
	{
		uint8_t makeNewMeasurement;
	} Command;

	SonarModule();
	void Start();
	void Execute();

private:

	struct
	{
		uint8_t newMeasure;
		long int echoStartTime_us;
		long int echoEndTime_us;
	} State;

	struct
	{
		uint8_t echoPin;
		uint8_t trigPin;

	} Config;

	void MeasureEcho();
	void UpdateReport();
};



#endif /* SONARMODULE_H_ */
