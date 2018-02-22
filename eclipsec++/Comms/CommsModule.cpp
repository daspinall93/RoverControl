/*
 * Comms.cpp
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */

#include "CommsModule.h"

CommsModule::CommsModule()
{
  /* SET ALL DATA MEMBERS TO 0 */
  memset(&Report, 0, sizeof(Report));
  memset(&Command, 0, sizeof(Report));
  memset(&SocketConfig, 0, sizeof(Report));
  memset(&SocketState, 0, sizeof(Report));
  memset(&MavConfig, 0, sizeof(Report));
  memset(&MavState, 0, sizeof(Report));

}

void CommsModule::Start()
{
    /* CONFIGURE SOCKET PARAMETERS */
    SocketConfig.socketLength = sizeof(struct sockaddr_in);
    SocketConfig.portNumber = GROUND_SOCKETNO;

    strcpy(SocketConfig.groundipAddr, GROUND_IP_ADDRESS);
    SocketConfig.socketLength = sizeof(struct sockaddr_in);

    /* SETUP THE SOCKET */
    //TODO Add error checking to the socket set up process
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

void CommsModule::Stop()
{
    //close the socket
    close(SocketConfig.socketNum);
}

void CommsModule::Execute()
{

    /* SEND A NEW PACKET */
    SendPacket();

    /* CHECK FOR ANY RECEIVED PACKETS */
    ReceivePacket();

    Debug();
}

void CommsModule::SendPacket()
{
    /* CHECK IF NEW SEND COMMAND HAS BEEN ISSUED */
    if (Command.newSendCommand == 1)
    {
	memset(&SocketState.bufferArray, 0, sizeof(SocketState.bufferArray));

	/* PRODUCE THE MESSAGE IN MAVLINK FORMAT */
	switch(Command.messageid)
	{

	case MAVLINK_MSG_ID_HEARTBEAT:

	    mavlink_msg_heartbeat_pack(MavConfig.sysid, MavConfig.compid, &Command.standard, Command.heartBeat.locom_mode, Command.heartBeat.motor1_mode, Command.heartBeat.motor2_mode);

	    break;

	default:

	    break;
	}

	/* STORE THE MESSAGE IN THE SOCKET BUFFER */
	SocketState.bufferLength = mavlink_msg_to_send_buffer(SocketState.bufferArray, &Command.standard);
	SocketState.bytesSent = sendto(SocketConfig.socketNum, SocketState.bufferArray,
			SocketState.bufferLength, 0, (struct sockaddr*) &SocketConfig.socketidGround, sizeof(struct sockaddr_in));

	/* UPDATE RELEVANT SOCKET STATE ENTRIES */
	SocketState.messagesSent += 1;
	Command.newSendCommand = 0;

    }
    else
    {
	/* SET BYTES SENT TO 0 TO SIGNIFY NO MESSAGE SENT */
	SocketState.bytesSent = 0;
	return;
    }
}

void CommsModule::ReceivePacket()
{
    memset(&SocketState.bufferArray, 0, sizeof(SocketState.bufferArray));

    /* CHECK ON NUMBER OF BYTES RECEIVED AND STORED IN THE BUFFER */
    SocketState.bytesReceived = recvfrom(SocketConfig.socketNum, SocketState.bufferArray,
	sizeof(SocketState.bufferArray), 0, (struct sockaddr*) &SocketConfig.socketidGround, (socklen_t*)&SocketConfig.socketLength);

    if (SocketState.bytesReceived != -1)
    {
	/* PARSE THE MESSAGE INTO GENERIC (PAYLOAD NOT PARSED) MAVLINK FORMAT */
	for (int i = 0; i < SocketState.bytesReceived; i++)
	{
		//printf("current byte: 0x%02x \n", SocketState.bufferArray[i]);
		if(mavlink_parse_char(MAVLINK_COMM_0, SocketState.bufferArray[i], &Report.standard, &MavState))
		{
			//printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
		}
	}

	Report.newPacketReceived = 1;

	/* CONVERT FROM GENERIC MAVLINK TO SPECIFIC MAVLINK (WITH PAYLOAD DECODED) */
	switch (Report.standard.msgid){

	case MAVLINK_MSG_ID_HEARTBEAT:

		break;

	case MAVLINK_MSG_ID_LOCOM_COMMAND:
		mavlink_msg_locom_command_decode(&Report.standard, &Report.locomCommand);
		break;

	}

    }
    else
    {
	/* NO NEW PACKETS RECEIVED */
	Report.newPacketReceived = 0;
	return;
    }
}

void CommsModule::Debug()
{
	printf("[COMMS]bytes sent = %d \n", SocketState.bytesSent);
	printf("[COMMS]bytes received = %d \n", SocketState.bytesReceived);
//	printf("[COMMS]locom_commandid = %d \n", Report.locomCommand.command_id);
//	printf("[COMMS]locom_duration = %d \n", Report.locomCommand.duration_ms);
//	printf("[COMMS]locom_power = %d \n", Report.locomCommand.power);
}


