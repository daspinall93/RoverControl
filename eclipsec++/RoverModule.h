/*
 * RoverModule.h
 * Module that will call execute and start functions and time calls
 *  Created on: 14 Feb 2018
 *      Author: dan
 */

#ifndef ROVERMODULE_H_
#define ROVERMODULE_H_
#include "LocomModule.h"
#include "CommsModule.h"
#include "MotorModule.h"
#include "TimerModule.h"

class RoverModule
{
public:
    //create the modules to be use and set as friends to access execute and start functions
    LocomModule Locom;
    CommsModule Comms;
    MotorModule Motor1;
    MotorModule Motor2;
    TimerModule Timer;


    void Start();
    void Execute();


};



#endif /* ROVERMODULE_H_ */
