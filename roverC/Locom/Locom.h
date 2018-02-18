/*
 * Locom.h
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

#ifndef LOCOM_LOCOM_H_
#define LOCOM_LOCOM_H_

/* INTERFACE (PUBLIC) DATA */
extern typedef struct
{
	int power;
	int durmsec;
	uint8_t commandid;
	uint8_t newCommand;
} Locom_Command;

extern typedef struct
{
	long int modeElapsedTime;
	uint8_t mode;
} Locom_Report;

/* INTERFACE (PUBLIC) FUNCTIONS */
extern void Start();
extern void Execute(Locom_Command* p_Locom_Command, Locom_Report* p_Locom_Report);

#endif /* LOCOM_LOCOM_H_ */
