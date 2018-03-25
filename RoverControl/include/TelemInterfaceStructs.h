/*
 * TelemInterfaceStructs.h
 *
 *  Created on: 24 Mar 2018
 *      Author: root
 */

#ifndef INCLUDE_TELEMINTERFACESTRUCTS_H_
#define INCLUDE_TELEMINTERFACESTRUCTS_H_

#include "mavlink/SoteriaRover/mavlink.h"

typedef struct __mavlink_telem_command_t
{
	// Structures to allow for Telem to produce buffer for comms
	mavlink_motor_report_t MotorReport;
	mavlink_sonar_report_t SonarReport;
	mavlink_inert_report_t InertReport;

} mavlink_telem_command_t;

typedef struct __mavlink_telem_report_t
{
	//buffer to be given to comms and its length
	unsigned char buffer[2041]; //buffer for comms to send
	int bufferLength; //length of the buffer
	int numMsgs; //number of messages in the buffer

} mavlink_telem_report_t;

#endif /* INCLUDE_TELEMINTERFACESTRUCTS_H_ */
