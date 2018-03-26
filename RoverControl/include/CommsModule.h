/*
 * Comms.h
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */

#ifndef CommsModule_H_
#define CommsModule_H_

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "CommsInterfaceStructs.h"


#define BUFFER_LENGTH 2041
#define GROUND_IP_ADDRESS "127.0.0.1"
#define ROVER_SOCKETNO 14550
#define GROUND_SOCKETNO 14550

class CommsModule
{
public:
//	CommsModule(int port, char* ip);
	void Start(int port, char* ip);
	void Execute(const mavlink_comms_command_t& CommsCommand_in,
			mavlink_comms_report_t& CommsReport_out);
	void Stop();

private:
	struct sockaddr_in inSocketId, outSocketId;//structures specifying the socket properties
	int inSocket;	//value to identify socket returned from socket()
	int outSocket;
	int socketLength;

	int outPortNum; //the port on the GS to connect to
	int inPortNum;
	char* outIpAddr;

	uint8_t bufferArray[BUFFER_LENGTH];
	int bufferLength;	//length of the buffer currently occupied
	int bytesSent;
	int bytesReceived;//used for checking number of bytes sent and received

	void TransmitData(const mavlink_comms_command_t& CommsCommand_in);
	void ReceiveData();
	void UpdateReport(mavlink_comms_report_t& CommsReport_out);
	void Debug();
};

#endif /* CommsModule_H_ */
