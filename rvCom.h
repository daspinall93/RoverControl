/*
 * rv_com.h
 *
 *  Created on: 27 Jan 2018
 *      Author: dan
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#ifndef RV_COM_H_
#define RV_COM_H_

#define RV_SERVER_ADDR "192.168.0.17"
#define RV_SOCKET 5000 //socket to connect to on server address

//configuration functions
uint8_t com_enable();
void com_disable();

//settings functions

//transmit functions
uint8_t com_send(const char* mes);

//receive functions
int com_recieve(char* rec_mes);

#endif /* RV_COM_H_ */
