/*
 * RoverModule.h
 * Module that will call execute and start functions and time calls
 *  Created on: 14 Feb 2018
 *      Author: dan
 */

#ifndef ROVERMODULE_H_
#define ROVERMODULE_H_

/* INCLUDES FOR INTERACTING WITH MODULES */
#include "../Locom/LocomModule.h"
#include "../Comms/CommsModule.h"
#include "../Motor/MotorModule.h"

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

  RoverModule(LocomModule* p_Locom_in, CommsModule* p_Comms_in, MotorModule* p_Motor1_in, MotorModule* p_Motor2_in);
  void Start();
  void Execute();

private:
  /* PRIVATE DATA MEMBER */
  struct
  {
    struct timespec tspec;	//used to retrieve the current time

    //current time
    long int milSec;

    //previous time when the flag was high used as reference for when flag should go high next
    long int onehzHighMilSec;
    long int tenhzHighMilSec;

    //flags for timings
    uint8_t onehzFlag;
    uint8_t tenhzFlag;
    //uint8_t 100hzFlag;
  } State;

  /* PRIVATE FUNCTIONS MEMBERS */
  void StartTimer();
  void UpdateState();
  void DistributeCommands();
  void Debug();
};



#endif /* ROVERMODULE_H_ */
