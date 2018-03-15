/*
 * Locom.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

/* TODO
 * -Incorporate ability to control the power being applied to the motors (PWM)
 * -
 */
#ifndef C___LOCOM_H_
#define C___LOCOM_H_

#include <stdio.h>
#include <stdint.h>
#include "../mavlink/SoteriaRover/mavlink.h"

class LocomModule
{
public:
	/* PUBLIC INTERFACE FOR OTHER OBJECTS TO INTERACT WITH */
	void Start();
	void Execute(mavlink_locom_report_t* p_LocomReport_out,
			mavlink_locom_command_t* p_LocomCommand_in,
			mavlink_motor_command_t* p_MotorCommand_out);

private:

	uint64_t modeStartTime_ms; /*< The ID of the locomotion module command*/
	uint64_t modeElapsedTime_ms; /*< The ID of the locomotion module command*/
	uint8_t mode; /*< duration of the locomotion command*/

	void ModeStop(mavlink_motor_command_t* p_MotorCommand_out,
			const mavlink_locom_command_t* p_LocomCommand_in);

	void ModeStraightForward(mavlink_motor_command_t* p_MotorCommand_out,
			const mavlink_locom_command_t* p_LocomCommand_in);

	void ModeStraightBackward(mavlink_motor_command_t* p_MotorCommand_out,
			const mavlink_locom_command_t* p_LocomCommand_in);

	void ModeTurnRight(mavlink_motor_command_t* p_MotorCommand_out,
			const mavlink_locom_command_t* p_LocomCommand_in);

	void ModeTurnLeft(mavlink_motor_command_t* p_MotorCommand_out,
			const mavlink_locom_command_t* p_LocomCommand_in);

	void UpdateReport(mavlink_locom_report_t* p_LocomReport_out);

	void
	Debug();

};

#endif /* C___LOCOM_H_ */
