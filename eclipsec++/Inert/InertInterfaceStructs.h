/*
 * InertInterfaceStructs.h
 *
 *  Created on: 26 Feb 2018
 *      Author: G.P Team 1
 */

#ifndef INERT_INERTINTERFACESTRUCTS_H_
#define INERT_INERTINTERFACESTRUCTS_H_


	typedef struct __mavlink_inert_report_t
	{
            /* ACCELEROMETER ADC VALUES */
	    int16_t accX_dig;
	    int16_t accY_dig;
	    int16_t accZ_dig;

	    /* GYRO ADC VALUES */
	    int16_t gyroX_dig;
	    int16_t gyroY_dig;
	    int16_t gyroZ_dig;
	} mavlink_inert_report_t;


#endif /* INERT_INERTINTERFACESTRUCTS_H_ */
