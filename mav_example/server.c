/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//#include "mavlink/v2.0/SoteriaRover/mavlink.h"

#define BUFFER_LENGTH 2041


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

//	mavlink_message_t msg;
//	mavlink_status_t status;
    struct sockaddr_in si_me, si_other;
    int s, i, blen, slen = sizeof(si_other);
    int bytes_received, bytes_sent;
    char buf[BUFFER_LENGTH];
    blen = sizeof(buf);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    int portno = atoi(argv[1]);

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*) &si_me, sizeof(si_me));

    i = 0;
    int j = 0;
//    mavlink_heartbeat_t hb;
    while (i < 1){

    	/* Receive the data from the client (rover) */
    	bytes_received = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &si_other, &slen);
    	printf("Number of bytes received = %d \n", bytes_received);
//    	for (j = 0; j < bytes_received; j++)
//    	{
//
//			if (mavlink_parse_char(MAVLINK_COMM_0, buf[j], &msg, &status))
//			{
//				// Packet received
//				printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
//			}
//
//    	}
//
//    	//message has been received and turned into a mavlink_message_t format
//    	//now need to decode the message
//    	mavlink_msg_heartbeat_decode(&msg, &hb);
//    	printf("Payload: \nLocom mode = %d \n", hb.Locom_mode);
//    	printf("mavlink_version = %d \n", hb.mavlink_version);
//
//    	/* SEND A COMMAND TO THE ROVER */
//    	mavlink_msg_locom_command_pack(2, 1, &msg, LOCOM_COMMAND_STRAIGHT_FORWARD, 3000, 50);
//		blen = mavlink_msg_to_send_buffer(buf, &msg);
//		bytes_sent = sendto(s, buf, blen, 0, (struct sockaddr*)&si_other, sizeof(struct sockaddr_in));
//    	printf("Number of bytes Sent: %d \n", bytes_sent);
    	memset(buf, 0, sizeof(buf));
    	i++;

    }

    close(s);
    return 0;
}

