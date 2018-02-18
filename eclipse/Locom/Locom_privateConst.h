/*
 * Locom_privateConst.h
 *
 *  Created on: 18 Feb 2018
 *      Author: dan
 */

#ifndef LOCOM_LOCOM_PRIVATECONST_H_
#define LOCOM_LOCOM_PRIVATECONST_H_

#define ENA 18	//PWM
#define ENB 19	//PWM
//M1=right motor
#define IN1 4	//dig for M1
#define IN2 17	//dig for M1
//M2 = left motor
#define IN3 27	//dig for M2
#define IN4 22	//dig for M2

//state of the wheels (forward, backward and stop)
#define LOCOM_WHEEL_FORWARD 1
#define LOCOM_WHEEL_BACKWARD 2
#define LOCOM_WHEEL_STOP 0

#define PI 3.14159265

#endif /* LOCOM_LOCOM_PRIVATECONST_H_ */
