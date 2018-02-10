/*
 * Motor.h
 *
 *  Created on: 10 Feb 2018
 *      Author: dan
 */

#ifndef MOTORCLASS_H_
#define MOTORCLASS_H_

#include <stdint.h>
#include <bcm2835.h>

#define MOTOR_COMMAND_STOP 0
#define MOTOR_COMMAND_FORWARD 1
#define MOTOR_COMMAND_BACKWARD 2

#define MOTOR_MODE_STOP 0
#define MOTOR_MODE_FORWARD 1
#define MOTOR_MODE_BACKWARD 2

class MotorClass{
public:

	//public data members
	struct {

		uint8_t commandid;
		bool newCommand;
		int power;

	} Command;

	struct {

	} Report;

	struct {

		uint8_t pwmPin;
		uint8_t inPin1;	//if high and pin2 low then wheel goes forward
		uint8_t inPin2;
		uint8_t motorid;

	} Parameters;

	//public function members
	MotorClass(){};
	void Start();
	void Execute();


private:

	struct {

		uint8_t mode;
		uint8_t speed;

	} State;

	void ModeStop();
	void ModeForward();
	void ModeBackward();

	void UpdateReport();
	void Debug();

protected:



};


#endif /* MOTORCLASS_H_ */
