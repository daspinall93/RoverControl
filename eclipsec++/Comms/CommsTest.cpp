/*
 * CommsTest.cpp
 *
 *  Created on: 24 Feb 2018
 *      Author: dan
 */
#include <unistd.h>
#include "CommsModule.h"
#include "../mavlink/SoteriaRover/mavlink.h"
#include "CommsInterfaceStructs.h"

uint8_t ParseMessages(mavlink_message_t* parsedMessages, const uint8_t* buffer,
		uint32_t bufferLength);

int main()
{
	CommsModule Comms = CommsModule();
	mavlink_comms_command_t CommsCommand;
	mavlink_comms_report_t CommsReport;

	Comms.Start();

	uint8_t buffer[2041];
	uint16_t bufferLength;
	mavlink_message_t msg;

	memset(&buffer, 0, 2041);

	/* GENERATE THE MAVLINK PACKET */
	int i=0;
	while (i < 10)
	{
		mavlink_msg_heartbeat_pack(255, 255, &msg, LOCOM_MODE_TURN_RIGHT,
				MOTOR_MODE_FORWARD, MOTOR_MODE_BACKWARD);
		bufferLength = mavlink_msg_to_send_buffer(buffer, &msg);

		CommsCommand.BufferLength = bufferLength;

		memcpy(CommsCommand.msgSentBuffer, buffer, bufferLength);

		Comms.Execute(&CommsCommand, &CommsReport);

		sleep(1);
		i++;
	}
	/* TEST DECODING THE MESSAGE RECEIVED FROM COMMS */
	if (CommsReport.numBytesRec > 0)
	{
		mavlink_message_t parsedMessages[10];

		uint8_t numMsgRec = ParseMessages(parsedMessages, CommsReport.msgRecBuffer,
				CommsReport.numBytesRec);

		for (int i = 0; i < numMsgRec; i++)
		{
			switch (parsedMessages[i].msgid)
			{
			case MAVLINK_MSG_ID_HEARTBEAT:
				printf("Locom mode = %d, Motor1 mode = %d, Motor2 mode = %d \n",
						mavlink_msg_heartbeat_get_locom_mode(parsedMessages),
						mavlink_msg_heartbeat_get_motor1_mode(parsedMessages+1),
						mavlink_msg_heartbeat_get_motor2_mode(parsedMessages+2));

			}
		}
	}

	Comms.Stop();

	return 0;
}

uint8_t ParseMessages(mavlink_message_t* parsedMessages, const uint8_t* buffer,
		uint32_t bufferLength)
{
	mavlink_status_t status;
	uint8_t msgNum = 0;
	uint16_t byteNum = 0;

	/* CYCLE THROUGH EVERY BYTE IN THE BUFFER*/
	while (byteNum < bufferLength)
	{
		/* PARSE EVERY MESSAGE IN THE BUFFER */
		while (mavlink_parse_char(MAVLINK_COMM_0, buffer[byteNum],
				(parsedMessages + msgNum), &status) != 1)
		{
			byteNum++;
		}

		msgNum++;
	}

	return msgNum;
}
