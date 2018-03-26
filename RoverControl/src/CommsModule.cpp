/*
 * Comms.cpp
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */

#include "mavlink.h"
#include "CommsModule.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void CommsModule::Start(int port, char* ip)
{
	std::cout << "[COMMS]Starting Module..." << std::endl;

	// Set ip address to send messages to and port to receive on and send to
	outIpAddr = ip;
	outPortNum = port + 1;
	inPortNum = port;

	//TODO Add error checking to the socket set up process
	inSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// Configure the socket for TC
	memset((char *) &inSocketId, 0, sizeof(inSocketId));
	inSocketId.sin_family = AF_INET;
	inSocketId.sin_port = htons(inPortNum);
	inSocketId.sin_addr.s_addr = INADDR_ANY;

	if (bind(inSocket, (struct sockaddr*) &inSocketId,
			sizeof(struct sockaddr)) == -1)
	{
		printf("Error on binding insocket, errno = %d \n", errno);
	}

	outSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset((char *) &outSocketId, 0, sizeof(struct sockaddr));

	// Configure socket for sending TM
	outSocketId.sin_family = AF_INET;
	outSocketId.sin_addr.s_addr = INADDR_ANY;
	outSocketId.sin_port = htons(outPortNum);

	if (bind(outSocket, (struct sockaddr*) &outSocketId,
			sizeof(struct sockaddr)) == -1)
	{
		printf("Error on binding output socket, errno = %d \n", errno);
	}

	outSocketId.sin_family = AF_INET;
	outSocketId.sin_addr.s_addr = inet_addr(outIpAddr);
	outSocketId.sin_port = htons(outPortNum);

	/* ATTEMPT TO MAKE NON-BLOCKING */
#if (defined __QNX__) | (defined __QNXNTO__)
	//if (fcntl(outSocket, F_SETFL, O_NONBLOCK | FASYNC) < 0)
	if (fcntl(inSocket, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
	//if (fcntl(outSocket, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
	if (fcntl(inSocket, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

	socketLength = sizeof(struct sockaddr_in);

	/* SET THE BUFFER ARRAY TO 0 */
	memset(bufferArray, 0, sizeof(bufferArray));
}

void CommsModule::Stop()
{
	/* CLOSE SOCKET */
	close(inSocket);
	close(outSocket);
}

void CommsModule::Execute(const mavlink_comms_command_t& CommsCommand_in,
		mavlink_comms_report_t& CommsReport_out)
{
	/* CHECK IF SEND BUFFER HAS ANYTHING IN IT */
	if (CommsCommand_in.bufferLength > 0)
	{
		/* SEND CONTENTS OF THE BUFFER TO GS */
		TransmitData(CommsCommand_in);
	}
	else
	{
		/* NO BYTES HAVE BEEN SENT */
		bytesSent = 0;
	}

	/* CHECK IF ANY DATA HAS BEEN RECEIVED */
	ReceiveData();

	UpdateReport(CommsReport_out);

	Debug();
}

void CommsModule::TransmitData(const mavlink_comms_command_t& CommsCommand_in)
{
	// Copy to local buffer
	memset(bufferArray, 0, sizeof(bufferArray));

	memcpy(bufferArray, CommsCommand_in.msgSendBuffer, CommsCommand_in.bufferLength);
	bufferLength = CommsCommand_in.bufferLength;

	bytesSent = sendto(outSocket, bufferArray, bufferLength, 0,
			(struct sockaddr*) &outSocketId, sizeof(struct sockaddr_in));

}

void CommsModule::ReceiveData()
{
	memset(bufferArray, 0, sizeof(bufferArray));

	/* CHECK ON NUMBER OF BYTES RECEIVED AND STORED IN THE BUFFER */
	bytesReceived = recvfrom(inSocket, bufferArray, sizeof(bufferArray), 0,
			(struct sockaddr*) &inSocketId, (socklen_t*) &socketLength);

	bufferLength = bytesReceived;

}

void CommsModule::UpdateReport(mavlink_comms_report_t& CommsReport_out)
{
	if (bytesReceived == -1)
	{
		/* SET BUFFER TO 0 WHEN NO BYTES WERE RECEIVED */
		memset(CommsReport_out.msgRecBuffer, 0, BUFFER_LENGTH);
	}
	else
	{
		/* COPY CONTENTS OF BUFFER TO THE REPORT */
		memcpy(CommsReport_out.msgRecBuffer, &bufferArray, bytesReceived);
	}
	CommsReport_out.numBytesRec = bytesReceived;
	CommsReport_out.numBytesSent = bytesSent;
}

void CommsModule::Debug()
{
	if (debugEnabled==true)
	{
		printf("[COMMS]bytes sent = %d \n", bytesSent);
		printf("[COMMS]bytes received = %d \n", bytesReceived);
	}
}

