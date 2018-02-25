/*
 * Comms.h
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */

#ifndef CommsModule_H_
#define CommsModule_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "CommsInterfaceStructs.h"


#define BUFFER_LENGTH 2041
#define GROUND_IP_ADDRESS "192.168.0.54"
#define ROVER_SOCKETNO 14550
#define GROUND_SOCKETNO 14550

class CommsModule
{
public:
	void Start();
	void Execute(const mavlink_comms_command_t* p_CommsCommand_in,
			mavlink_comms_report_t* p_CommsReport_out);
	void Stop();

private:
	struct sockaddr_in socketidRover, socketidGround;//structures specifying the socket properties
	int socketNum;	//value to identify socket returned from socket()
	int socketLength;

	int groundPortNum; //the port on the GS to connect to
	int roverPortNum;
	char groundipAddr[100];

	uint8_t bufferArray[BUFFER_LENGTH];
	int bufferLength;	//length of the buffer currently occupied
	int bytesSent;
	int bytesReceived;//used for checking number of bytes sent and received

	void TransmitData(const mavlink_comms_command_t* p_CommsCommand_in);
	void ReceiveData();
	void UpdateReport(mavlink_comms_report_t* p_CommsReport_out);
	void Debug();
};

#endif /* CommsModule_H_ */
