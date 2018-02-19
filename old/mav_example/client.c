/*
 * client_example.c
 *
 *  Created on: 11 Feb 2018
 *      Author: dan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "mavlink/v2.0/SoteriaRover/mavlink.h"

#define BUFFER_LENGTH 2041

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

	mavlink_message_t msg;
	mavlink_locom_command_t lc_msg;
	mavlink_status_t status;
    struct sockaddr_in si_me, si_other;
    int s, i, blen, slen = sizeof(si_other);
    int bytes_sent, bytes_received;
    uint8_t buf[BUFFER_LENGTH];

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset((char *) &si_me, 0, sizeof(si_me));

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    int portno = atoi(argv[1]);

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*) &si_me, sizeof(si_me));

	//configure server address
    memset((char *) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_addr.s_addr = inet_addr("127.0.0.1");
	si_other.sin_port = htons(portno);

	i = 0;
	int j = 0;
    while (i < 1){

		/* SEND HEARTBEAT*/
		mavlink_msg_heartbeat_pack(1, 1, &msg, LOCOM_MODE_STRAIGHT_FORWARD);	//send a heartbeat TM packet
		blen = mavlink_msg_to_send_buffer(buf, &msg);

		bytes_sent = sendto(s, buf, blen, 0, (struct sockaddr*)&si_other, sizeof(struct sockaddr_in));
    	printf("Number of bytes Sent: %d \n", bytes_sent);
    	i++;

    	/* WAIT FOR COMMAND */
    	bytes_received = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*) &si_other, &slen);
    	printf("Number of bytes received = %d \n", bytes_received);
    	for (j = 0; j < bytes_received; j++)
    	{

			if (mavlink_parse_char(MAVLINK_COMM_0, buf[j], &msg, &status))
			{
				// Packet received
				printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
			}

    	}

    	//message has been received and turned into a mavlink_message_t format
    	//now need to decode the message
    	mavlink_msg_locom_command_decode(&msg, &lc_msg);
    	printf("Payload: \ncommandid = %d \n", lc_msg.Locom_commandid);
    	printf("power = %d \n", lc_msg.power);
    	printf("duration(ms) = %d \n", lc_msg.duration_ms);

    	sleep(1);

    }

    close(s);
    return 0;
}
