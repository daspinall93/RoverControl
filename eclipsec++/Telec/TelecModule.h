/*
 * TmTcModule.h
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */

#ifndef TELEC_TELECMODULE_H_
#define TELEC_TELECMODULE_H_

#include "../Comms/CommsModule.h"
#include "../Motor/MotorModule.h"
#include "../Locom/LocomModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include "../Comms/CommsInterfaceStructs.h"
#include "TelecInterfaceStructs.h"
#define MSG_BUFFER_SIZE 10

class TelecModule
{
public:
	void Start();
	void Execute(mavlink_telec_report_t* p_TelecReport_out,
			mavlink_comms_report_t* p_CommsReport_in);

private:
	uint8_t buffer[2041];
	uint16_t bufferLength;
	mavlink_status_t mavlinkStatus;
	mavlink_message_t parsedMsgs[MSG_BUFFER_SIZE]; //buffer containing the TC from GS
	uint8_t numParsedMsgs;

	void ParseMessages(const mavlink_comms_report_t* p_CommsReport_in);
	void UpdateReport(mavlink_telec_report_t* p_TmTcReport_out);
	void EncodeMessages();

	void Debug();

};

#endif /* TELEC_TELECMODULE_H_ */
