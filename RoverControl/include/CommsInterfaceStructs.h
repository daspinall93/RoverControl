/*
 * CommsInterfaceStructs.h
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */

#ifndef COMMS_COMMSINTERFACESTRUCTS_H_
#define COMMS_COMMSINTERFACESTRUCTS_H_

typedef struct __mavlink_comms_report_t {
	int32_t numBytesRec; /*< */
	int32_t numBytesSent; /*< */
	uint8_t msgRecBuffer[2041]; /*< */
} mavlink_comms_report_t;

typedef struct __mavlink_comms_command_t {
	int32_t BufferLength; /*< */
	uint8_t msgSendBuffer[2041]; /*< */
} mavlink_comms_command_t;

#endif /* COMMS_COMMSINTERFACESTRUCTS_H_ */
