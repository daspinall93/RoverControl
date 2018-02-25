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

#include "../mavlink/SoteriaRover/mavlink.h"

class MotorModule{
public:
    void Start();
    void Execute(mavlink_motor_command_t* p_MotorCommand_in, mavlink_motor_report_t* p_MotorReport_out);

private:

	uint8_t m1_mode;
	uint32_t m1_pwmInput;
	uint8_t m2_mode;
	uint32_t m2_pwmInput;

	uint8_t m1_pwmPin;
	uint8_t m1_inPin1;	//if high and pin2 low then wheel goes forward
	uint8_t m1_inPin2;
	uint8_t m1_pwmChannel;	//the channel on t
	uint8_t m2_pwmPin;
	uint8_t m2_inPin1;	//if high and pin2 low then wheel goes forward
	uint8_t m2_inPin2;
	uint8_t m2_pwmChannel;	//the channel on t


	uint32_t pwmRange;

    void ModeStop(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);
    void ModeForward(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);
    void ModeBackward(const mavlink_motor_command_t* p_MotorCommand_in, uint8_t motorid);
    void UpdateReport(mavlink_motor_report_t* p_MotorReport_out);
    void Debug();
    uint32_t CalculatepwmData(uint32_t power_per);


};

#endif /* MOTORCONTAINER_H_ */
