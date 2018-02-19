/*
 * RoverModule.h
 * Module that will call execute and start functions and time calls
 *  Created on: 14 Feb 2018
 *      Author: dan
 */

#ifndef ROVERMODULE_H_
#define ROVERMODULE_H_

/* INCLUDES FOR INTERACTING WITH MODULES */
#include "LocomModule.h"
#include "CommsModule.h"
#include "MotorModule.h"

class RoverModule
{
public:
  //create the modules to be use and set as friends to access execute and start functions
  LocomModule* p_Locom;
  CommsModule* p_Comms;
  MotorModule* p_Motor1;
  MotorModule* p_Motor2;
//  LocalModule* p_Local;

  struct
  {

  } Report;

  struct
  {

  } Config;

  RoverModule(){};
  void Start(LocomModule* p_Locom, CommsModule* p_Comms, MotorModule* p_Motor1, MotorModule* p_Motor2);
  void Execute();

private:
  /* PRIVATE DATA MEMBER */
  struct
  {
    struct timespec tspecInit;	//time at which the timer was started
    struct timespec tspec;	//used to retrieve the current time

    //current time
    long int milSec;
    long int microSec;

    //previous time used to check if flag should be high or low
    long int prevMilSec;
    long int prevMicroSec;

    //flags for timings
    uint8_t onehzFlag;
    uint8_t tenhzFlag;
    //uint8_t 100hzFlag;
  } State;

  /* PRIVATE FUNCTIONS MEMBERS */
  void StartTimer();
  void UpdateState();
  void DistributeCommands();
};



#endif /* ROVERMODULE_H_ */
