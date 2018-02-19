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
#include "../Motor/MotorModule.h"

class LocomModule
{
public:
    struct
    {
	long int modeElapsedTime;
	uint8_t mode;	//a valid submode using LOCOM_STATE_x
    } Report;

    struct
    {
	int power;	//power (0 to 100%)
	int durmsec;	//duration in msec
	uint8_t commandid;	//command using valid LOCOM_COMMAND_x
	bool newCommand;	//boolean for if a new command has been produced
    } Command;

    LocomModule(MotorModule* p_M1, MotorModule* p_M2);	//replace locom_start()
    void Start();
    void Execute();

private:
    MotorModule* p_Motor1;
    MotorModule* p_Motor2;

    struct
    {
	//struct containing to keep track of internal state of the object
	long int modeStartTime;
	long int modeElapsedTime;
	uint8_t mode;
    } State;

    struct
    {

    } Config;

    void ModeStop();
    void ModeStraightForward();
    void ModeStraightBackward();
    void ModeTurnRight();
    void ModeTurnLeft();

    void UpdateReport();
    void Debug();

};

#endif /* C___LOCOM_H_ */
