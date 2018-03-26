/*
 * TelemModule.cpp
 *
 *  Created on: 24 Mar 2018
 *      Author: root
 */

#include "TelemModule.h"
#include <iostream>

#define SOURCE_ID 1 // source if for mavlink
void TelemModule::Start(void)
{

}

void TelemModule::Execute(const mavlink_telem_command_t& TelemCommand_in,
		mavlink_telem_report_t& TelemReport_out)
{
	//set the message structure to empty
	memset((char*) &mavMsg, 0, sizeof(mavMsg));
	msgLength = 0;

	// Ensure buffer is clear first and buffer length set
	memset(buffer, 0, sizeof(buffer));
	bufferLength = 0;

	// Take the current version of each mdoules report and place in buffer
	EncodeTelem(TelemCommand_in);

	// Pass the created buffer into the report
	UpdateReport(TelemReport_out);

	Debug();
}

void TelemModule::Stop(void)
{

}

void TelemModule::EncodeTelem(const mavlink_telem_command_t& TelemCommand_in)
{
	// Construct the heartbeat message to be sent back
	mavTM.pitch_deg = TelemCommand_in.InertReport.pitch_deg;
	mavTM.roll_deg = TelemCommand_in.InertReport.roll_deg;
	mavTM.yaw_deg = TelemCommand_in.InertReport.yaw_deg;
	mavTM.objDist_cm = TelemCommand_in.SonarReport.objectDistance_cm;
	mavTM.motor_mode = TelemCommand_in.MotorReport.mode;
	mavTM.modeDur_ms = TelemCommand_in.MotorReport.modeElapsedTime_ms;
	mavTM.tiltFlag = TelemCommand_in.InertReport.tiltFlag;
	mavTM.objDetFlag = TelemCommand_in.SonarReport.objectDetected_flag;

	// Encode and pack the motor report
	msgLength = mavlink_msg_heartbeat_encode(SOURCE_ID, 1, &mavMsg, &mavTM);
	bufferLength = mavlink_msg_to_send_buffer(buffer, &mavMsg);

}

void TelemModule::UpdateReport(mavlink_telem_report_t& TelemReport_out)
{
	// Put the generated buffer into the telem report buffer
	memcpy(TelemReport_out.buffer, buffer,
			bufferLength);
	TelemReport_out.bufferLength = bufferLength;

}

void TelemModule::Debug(void)
{
	if (debugEnabled==true)
	{
		std::cout << "[TELEM]Message Length = " << msgLength << std::endl;
		std::cout << "[TELEM]Buffer Length = " << bufferLength << std::endl;
	}
}

