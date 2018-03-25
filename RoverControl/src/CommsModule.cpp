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

void CommsModule::Start(int port, char* ip)
{
	std::cout << "[COMMS]Starting Module..." << std::endl;

	// Set ip address to send messages to and port to receive on and send to
	groundipAddr = ip;
	groundPortNum = port;
	roverPortNum = port;

	/* SETUP THE ROVER SOCKET */
	//TODO Add error checking to the socket set up process
	socketNum = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//configure the socket for use
	memset((char *) &socketidRover, 0, sizeof(socketidRover));
	socketidRover.sin_family = AF_INET;
	socketidRover.sin_port = htons(roverPortNum);
	socketidRover.sin_addr.s_addr = INADDR_ANY;

	if (bind(socketNum, (struct sockaddr*) &socketidRover,
			sizeof(struct sockaddr)) == -1)
	{
		printf("Error on binding \n");
	}

	/* ATTEMPT TO MAKE NON-BLOCKING */
#if (defined __QNX__) | (defined __QNXNTO__)
	if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
	if (fcntl(socketNum, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

	memset((char *) &socketidGround, 0, sizeof(struct sockaddr));

	/* GROUND SOCKET CONFIG */
	socketLength = sizeof(struct sockaddr_in);
	socketidGround.sin_family = AF_INET;
	socketidGround.sin_addr.s_addr = inet_addr(groundipAddr);
	socketidGround.sin_port = htons(groundPortNum);

	/* SET THE BUFFER ARRAY TO 0 */
	memset(bufferArray, 0, sizeof(bufferArray));
}

void CommsModule::Stop()
{
	/* CLOSE SOCKET */
	close(socketNum);
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

	bytesSent = sendto(socketNum, CommsCommand_in.msgSendBuffer, CommsCommand_in.bufferLength, 0,
			(struct sockaddr*) &socketidGround, sizeof(struct sockaddr_in));

}

void CommsModule::ReceiveData()
{
	memset(bufferArray, 0, sizeof(bufferArray));

	/* CHECK ON NUMBER OF BYTES RECEIVED AND STORED IN THE BUFFER */
	bytesReceived = recvfrom(socketNum, bufferArray, sizeof(bufferArray), 0,
			(struct sockaddr*) &socketidGround, (socklen_t*) &socketLength);

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
	printf("[COMMS]bytes sent = %d \n", bytesSent);
	printf("[COMMS]bytes received = %d \n", bytesReceived);
}

