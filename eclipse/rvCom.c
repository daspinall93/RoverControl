/*
 * rv_com.c
 * responsible for transmitting and receiving data from ground
 *  Created on: 27 Jan 2018
 *      Author: dan
 */
#include "rvCom.h"



int sockfd, n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];

/*
 * Function to start seperate process that will handle the comms connect to the server (i.e ground station)
 * Parameters - port_no is the port number to connect to the server
 * Returns - either 0 (unsuccessful) or 1 (successful)
 */
uint8_t com_enable(){

	//TODO error checking
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr,"ERROR opening socket\n");
		return 0;

	}

	//get server in correct format
	server = gethostbyname(RV_SERVER_ADDR);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        return 0;
    }

    //setup and connect
    bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(RV_SOCKET);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        fprintf(stderr,"ERROR connecting\n");
		return 0;
	}

	return 1;

}

void com_disable(){

	close(sockfd);

}

/*
 * Pass a string to send to the server
 * Params - message to send to server
 * Returns - 0 (unsuccessful) or 1 (successful)
 */
uint8_t com_send(const char* mes){

	bzero(buffer, sizeof(buffer));
	sprintf( buffer, "%s", mes);

	if (write(sockfd,buffer,strlen(buffer)) < 0){
        fprintf(stderr,"ERROR connecting\n");
		return 0;
	}

	return 1;
}

/*
 * Read a message from the server (in fd)
 * Params - a pointer to the string array to store the message
 * Returns - number of bytes read from the fd
 */
int com_recieve(char* rec_mes){

	//set the array input to 0 and read from the fd to buffer
	bzero(buffer, sizeof(buffer));
	n = read(sockfd, buffer, sizeof(buffer));

	//copy the buffer value to the rec_mes
	strcpy(rec_mes, buffer);
	return n;

}



