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
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "../mavlink/v2.0/SoteriaRover/mavlink.h"

#define BUFFER_LENGTH 2041
#define GROUND_IP_ADDRESS "127.0.0.1"
#define GROUND_SOCKETNO 14554

class CommsModule
{
public:
    /* MAVLINK INPUT DATA */
    //mav messages which can then be accessed as the output of the module (i.e heartBeat.mavLink_version)
    struct
    {
	uint8_t newPacketReceived;	//flag signifying whether a new packet was received on the last pass
	mavlink_message_t standard;	//the base type used retrieve the data with payload not decoded
	mavlink_heartbeat_t heartBeat;	//heartbeat message sent periodically
	mavlink_locom_command_t  locomCommand;	//command for the locomotion module
    } Report;

    //structure containing the input structures for each of the packets to be used
    //the corresponding structure values will need to be set before the call of the send function
    struct
    {
	//socket command
	uint8_t newSendCommand;

	//mav link command
	uint8_t messageid;	// message id to specify which packet is goin is going to be sent
	mavlink_message_t standard;	// the base type used to store the data from mavlink
	mavlink_heartbeat_t heartBeat;	// members are accessed as input for TM to ground
	mavlink_locom_command_t  locomCommand;	//members are accessed as input for TM to ground
    } Command;
    /* PUBLIC FUNCTION MEMBERS */

    CommsModule();
    void Start();
    void Execute();
    void Stop();

private:
    /* PRIVATE DATA MEMBERS */
    /* SOCKET DATA */
    //structure containing the parameters for the socket configuration
    struct
    {
	struct sockaddr_in socketidRover, socketidGround;	//structures specifying the socket properties
	int socketNum;	//value to identify socket returned from socket()
	int bufferLength;
	int socketLength;

	int portNumber; //the port on the GS to connect to
	char groundipAddr[100];
    } SocketConfig;

    struct
    {
	uint8_t bufferArray[BUFFER_LENGTH];
	int bufferLength;	//length of the buffer currently occupied
	int bytesSent;
	int bytesReceived;	//used for checking number of bytes sent and received
	int messagesSent;
	int messagesReceived;
    } SocketState;

    /* MAVLINK DATA */
    //structure containing the various mavlink message types

    struct
    {
	uint8_t sysid;
	uint8_t compid;
    } MavConfig;

    mavlink_status_t MavState;	//parameters used to monitor mavlink

    /* PRIVATE FUNCTION MEMBERS */
    void SendPacket();
    void ReceivePacket();
    void Debug();
};

#endif /* CommsModule_H_ */
