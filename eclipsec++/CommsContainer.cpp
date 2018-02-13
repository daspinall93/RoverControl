/*
 * Comms.cpp
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */

#include "CommsContainer.h"

CommsContainer::CommsContainer()
{
	// TODO Auto-generated constructor stub
	SocketConfig.socketLength = sizeof(struct sockaddr_in);
	SocketConfig.portNumber = 9006;

	strcpy(SocketConfig.groundipAddr, GROUND_IP_ADDRESS);
	SocketConfig.socketLength = sizeof(struct sockaddr_in);

	//set all buffers to 0
	memset(&MavOutput, 0, sizeof(MavOutput));
	memset(&MavInput, 0, sizeof(MavInput));
}

CommsContainer::~CommsContainer()
{
	// TODO Auto-generated destructor stub
}

/* Create the socket connection */
void CommsContainer::Start()
{
	//TODO Add error checking to the socket set up process
	//create a socket
	SocketConfig.socketNum = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset((char *) &SocketConfig.socketidRover, 0, sizeof(SocketConfig.socketidRover));

	//configure the socket for use
	SocketConfig.socketidRover.sin_family = AF_INET;
	SocketConfig.socketidRover.sin_port = htons(SocketConfig.portNumber);
	SocketConfig.socketidRover.sin_addr.s_addr = INADDR_ANY;

	bind(SocketConfig.socketNum, (struct sockaddr*) &SocketConfig.socketidRover, sizeof(struct sockaddr));

	/* Attempt to make it non blocking */
#if (defined __QNX__) | (defined __QNXNTO__)
	if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
	if (fcntl(SocketConfig.socketNum, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

	memset((char *) &SocketConfig.socketidGround, 0, sizeof(struct sockaddr));

	//configure the port to be sending messages to
	SocketConfig.socketidGround.sin_family = AF_INET;
	SocketConfig.socketidGround.sin_addr.s_addr = inet_addr(SocketConfig.groundipAddr);
	SocketConfig.socketidGround.sin_port = htons(SocketConfig.portNumber);
}

/* Execute will either receive or send messages over the connection created by Start() */
void CommsContainer::Execute()
{
	//as an example send heartbeat

	SendPacket();

	ReceivePacket();

	Debug();
}

void CommsContainer::Stop()
{
	//close the socket
	close(SocketConfig.socketNum);
}

/* Send a packet depending on the value of messageid */
void CommsContainer::SendPacket()
{
	if (MavInput.newSendCommand == 1)
	{
		//clear the buffer socket before sending
		memset(&SocketState.bufferArray, 0, sizeof(SocketState.bufferArray));

		//switch according to what messageid is set to
		switch(MavInput.messageid)
		{
		case MAVLINK_MSG_ID_HEARTBEAT:
			//send a heartbeat message
			//create the message in mavLink format
			mavlink_msg_heartbeat_pack(MavConfig.sysid, MavConfig.compid, &MavOutput.standard, MavInput.heartBeat.Locom_mode);

			break;

		default:

			break;
		}

		//pass to buffer and send to Ground
		SocketState.bufferLength = mavlink_msg_to_send_buffer(SocketState.bufferArray, &MavOutput.standard);
		SocketState.bytesSent = sendto(SocketConfig.socketNum, SocketState.bufferArray,
				SocketState.bufferLength, 0, (struct sockaddr*) &SocketConfig.socketidGround, sizeof(struct sockaddr_in));

		//update messages sent and newCommand flag
		SocketState.messagesSent += 1;
		MavInput.newSendCommand = 0;

	}
	else
	{
		SocketState.bytesSent = 0;
		return;
	}
}

void CommsContainer::ReceivePacket()
{
	memset(&SocketState.bufferArray, 0, sizeof(SocketState.bufferArray));

	SocketState.bytesReceived = recvfrom(SocketConfig.socketNum, SocketState.bufferArray,
			sizeof(SocketState.bufferArray), 0, (struct sockaddr*) &SocketConfig.socketidGround, (socklen_t*)&SocketConfig.socketLength);

	if (SocketState.bytesReceived != -1)
	{
		//data was received
		//parse the received packet

		for (int i = 0; i < SocketState.bytesReceived; i++)
		{
			//printf("current byte: 0x%02x \n", SocketState.bufferArray[i]);
			if(mavlink_parse_char(MAVLINK_COMM_0, SocketState.bufferArray[i], &MavOutput.standard, &mavlinkState))
			{
				//printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
			}

		}

		MavOutput.newPacketReceived = 1;
		//switch depending on the message id received and then set the corresponding output structure
		switch (MavOutput.standard.msgid){

		case MAVLINK_MSG_ID_HEARTBEAT:

			break;

		case MAVLINK_MSG_ID_LOCOM_COMMAND:
			mavlink_msg_locom_command_decode(&MavOutput.standard, &MavOutput.locomCommand);
			break;

		}

	}
	else
	{
		//no new packet was received so set the flag to false
		MavOutput.newPacketReceived = 0;
		return;
	}
}

void CommsContainer::Debug()
{
//	printf("[COMMS]bytes sent = %d \n", SocketState.bytesSent);
//	printf("[COMMS]bytes received = %d \n", SocketState.bytesReceived);
	printf("[COMMS]locom_commandid = %d \n", MavOutput.locomCommand.Locom_commandid);
	printf("[COMMS]locom_duration = %d \n", MavOutput.locomCommand.duration_ms);
	printf("[COMMS]locom_power = %d \n", MavOutput.locomCommand.power);
}


