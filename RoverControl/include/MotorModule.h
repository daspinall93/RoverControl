/*
 * Motor.h
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

/*
 * TODO:
 * -Include pwm control of pins ENA and ENB
 *
 */
#ifndef MOTORCONTAINER_H_
#define MOTORCONTAINER_H_


#include <stdint.h>

#include "mavlink/SoteriaRover/mavlink.h"

class MotorModule{
public:
    void Start();
    void Execute(mavlink_motor_command_t* p_MotorCommand_in, mavlink_motor_report_t* p_MotorReport_out);
    void Stop();

private:

	uint8_t m1_subMode;
	uint32_t m1_pwmInput;
	uint8_t m2_subMode;
	uint32_t m2_pwmInput;

	uint8_t m1_pwmPin;
	uint8_t m1_inPin1;	//if high and pin2 lo then wheel goes forward
	uint8_t m1_inPin2;
	uint8_t m1_pwmChannel;	//the channel on t
	uint8_t m2_pwmPin;
	uint8_t m2_inPin1;	//if high and pin2 low then wheel goes forward
	uint8_t m2_inPin2;
	uint8_t m2_pwmChannel;	//the channel on t

	uint64_t modeStartTime_ms; /*< The ID of the locomotion module command*/
	uint64_t modeElapsedTime_ms; /*< The ID of the locomotion module command*/
	uint8_t mode; /*< duration of the locomotion command*/

	uint32_t pwmRange;

	/* MODULE MODES */
	void ModeStop(mavlink_motor_command_t* p_MotorCommand_in);
	void ModeStraightForward(mavlink_motor_command_t* p_MotorCommand_in);
	void ModeStraightBackward(mavlink_motor_command_t* p_MotorCommand_in);
	void ModeTurnRight(mavlink_motor_command_t* p_MotorCommand_in);
	void ModeTurnLeft(mavlink_motor_command_t* p_MotorCommand_in);

	/* MODES FOR EACH MOTOR */
    void SubModeStop(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);
    void SubModeForward(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);
    void SubModeBackward(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);

    void UpdateReport(mavlink_motor_report_t* p_MotorReport_out);
    void Debug();
    uint32_t CalculatepwmData(uint32_t power_per);


};

#endif /* MOTORCONTAINER_H_ */
