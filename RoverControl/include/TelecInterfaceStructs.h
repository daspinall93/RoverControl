/*
 * TmTcStructs.h
 *
 *  Created on: 25 Feb 2018
 *      Author: dan
 */

#ifndef TELEC_TELECINTERFACESTRUCTS_H_
#define TELEC_TELECINTERFACESTRUCTS_H_

#include "mavlink.h"

/* CONTAIN THE COMMAND STRUCTURE OF THE APPROPRIATE COMMAND */
typedef struct __mavlink_telec_report_t {
	/* TC */
	uint8_t newTc;
	uint8_t msgid;
	mavlink_motor_command_t MotorCommand;
	mavlink_sonar_command_t SonarCommand;
	mavlink_inert_command_t InertCommand;
} mavlink_telec_report_t;



#endif /* TELEC_TELECINTERFACESTRUCTS_H_ */
