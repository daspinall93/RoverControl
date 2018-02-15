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
#include "mavlink/v2.0/SoteriaRover/mavlink.h"
#include <bcm2835.h>

#define PWM_ENABLED 0
#define PWM_RANGE 1024

class MotorModule{
public:
	//public data members
	//the command interface for motor to be called
	struct
	{
		uint8_t commandid;	//forward, backard or stop
		bool newCommand;	//flag for new command
		int power;	//power for the pwm
		int pwmData;	//the corresponding pwm output for the power provided
	} Command;

	//the report interface for caller to see
	struct
	{
		uint8_t mode;	//flag specifying if the motor currently has a voltage applied
	} Report;

	//public function members
	MotorModule(){};

	struct {

		uint8_t mode;
		uint8_t speed;

	} State;

	void ModeStop();
	void ModeForward();
	void ModeBackward();
	void calculatepwmData();

	void UpdateReport();
	void Debug();

	struct
	{
		uint8_t motorid;

		uint8_t pwmPin;
		uint8_t inPin1;	//if high and pin2 low then wheel goes forward
		uint8_t inPin2;

		uint8_t pwmChannel;	//the channel on t
		uint8_t pwmRange;
	} Config;


	void Start(uint8_t motorid);
	void Execute();



};


#endif /* MOTORCONTAINER_H_ */
