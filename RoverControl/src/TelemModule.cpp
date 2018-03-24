/*
 * TelemModule.cpp
 *
 *  Created on: 24 Mar 2018
 *      Author: root
 */

#include "TelemModule.h"

#define SOURCE_ID 1 // source if for mavlink
void TelemModule::Start(void)
{

}

void TelemModule::Execute(const mavlink_telem_command_t* p_TelemCommand_in,
		mavlink_telem_report_t* p_TelemReport_out)
{
	//set the message structure to empty
	memset((char*) &mavMsg, 0, sizeof(mavMsg));
	msgLength = 0;

	// Take the current version of each mdoules report and place in buffer
	EncodeTelem(p_TelemCommand_in);

	// Pass the created buffer into the report
}

void TelemModule::Stop(void)
{

}

void TelemModule::EncodeTelem(const mavlink_telem_command_t* p_TelemCommand_in)
{
	// Construct the heartbeat message to be sent back
	mavTM.pitch_deg = p_TelemCommand_in->InertReport.pitch_deg;
	mavTM.roll_deg = p_TelemCommand_in->InertReport.roll_deg;
	mavTM.yaw_deg = p_TelemCommand_in->InertReport.yaw_deg;
	mavTM.objDist_cm = p_TelemCommand_in->SonarReport.objectDistance_cm;
	mavTM.motor_mode = p_TelemCommand_in->MotorReport.mode;
	mavTM.modeDur_ms = p_TelemCommand_in->MotorReport.modeElapsedTime_ms;
	mavTM.tiltFlag = p_TelemCommand_in->InertReport.tiltFlag;
	mavTM.objDetFlag = p_TelemCommand_in->SonarReport.objectDetected_flag;

	// Encode and pack the motor report
	msgLength = mavlink_msg_motor_report_encode(SOURCE_ID, 1, &mavMsg, &mavTM);
	bufferLength = mavlink_msg_to_send_buffer(buffer, &mavMsg);

}

void TelemModule::UpdateReport(mavlink_telem_report_t* p_TelemReport_out)
{
	// Put the generated buffer into the telem report buffer
	memcpy(p_TelemReport_out->buffer, buffer,
			bufferLength);

}

void Debug(void)
{

}

