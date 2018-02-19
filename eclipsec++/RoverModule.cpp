/*
 * RoverModule.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: dan
 */
#include "RoverModule.h"

/* INCLUDES FOR TIMING PURPOSES */
#include <time.h>
#include <math.h>

/* INCLUDED FOR THE COMMAND INTERPRITATION FUNCTION */
#include "mavlink/v2.0/SoteriaRover/mavlink.h"
RoverModule::RoverModule()
{
    memset(&Report, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Report));
    memset(&State, 0, sizeof(Report));

}

void RoverModule::Start(LocomModule* p_Locom, CommsModule* p_Comms, MotorModule* p_Motor1, MotorModule* p_Motor2)
{
  /* START THE COMMS MODULE */
  p_Comms->Start();

  /* START MOTOR WITH ID=0 */
  p_Motor1->Start(0);

  /* START MOTOR WITH ID=1 */
  p_Motor2->Start(1);

  /* START LOCOM WITH MOTORS 1 & 2 */
  p_Locom->Start();

  /* START THE ROVER MODULES TIMER */
  StartTimer();
}

void RoverModule::Execute()
{
  while (1)
  {
    /* UPDATE TIMER FLAGS */
    UpdateState();

    /* EXECUTE MODULES AT 1HZ */
    if (State.onehzFlag)
    {
      continue;
    }

    /* EXECUTE MODULES AT 10HZ */
    if (State.tenhzFlag)
    {
      /* EXECUTE THE COMMS MODULE */
      p_Comms->Execute();


      /* TAKE THE COMMANDS RECEIVED AND DISTRIBUTE TO OTHER MODULES INPUTS */
      if (p_Comms->Report.newPacketReceived)
      {
	DistributeCommands();
      }

      /* EXECUTE THE LOCALISATION MODULE */
      //p_Local->Execute();

      /* EXECUTE THE LOCOMOTION MODULE */
      p_Locom->Execute();

      /* EXECUTE BOTH MOTOR MODULES */
      p_Motor1->Execute();
      p_Motor2->Execute();

    }
  }
}

void RoverModule::StartTimer()
{
  /* SET TIME AT WHICH THE ROVER STARTED */
  clock_gettime(CLOCK_MONOTONIC, &State.tspecInit);

  //set initial value of the time
  State.milSec = round(State.tspecInit.tv_nsec / 1.0e6);
  State.milSec = State.microSec + (State.tspecInit.tv_sec * 1000);

  State.prevMilSec = round(State.tspecInit.tv_nsec / 1.0e6);
  State.prevMilSec = State.prevMilSec + (State.tspecInit.tv_sec * 1000);

}

void RoverModule::UpdateState()
{
  /* UPDATE THE TIME */
  //update the times
  clock_gettime(CLOCK_MONOTONIC, &State.tspec);

  //set the previous time to the current time
  State.prevMilSec = State.milSec;

  //set the new time
  State.milSec = round(State.tspec.tv_nsec / 1.0e6);
  State.milSec = State.microSec + (State.tspecInit.tv_sec * 1000);

  /* UPDATE FLAGS */
  //the difference in time between the last call and the current
  long int delta = State.milSec - State.prevMilSec;

  //turn on the flag if 100ms have passed since the last call
  if (delta > 100)
  {
    Report.onehzFlag = 1;
  }
  else
  {
    Report.onehzFlag = 0;
  }

  //turn on the flag if 10ms have passed since the last call
  if (delta < 10)
  {
    Report.tenhzFlag = 1;
  }
  else
  {
    Report.tenhzFlag = 0;
  }
}

void RoverModule::DistributeCommands()
{
  /* IF NEW COMMAND IS RECEIVED TRANSFER INFORMATION TO THE MODULE COMMAND INPUT */
  switch (p_Comms->Report.standard.msgid)
  {
  case MAVLINK_MSG_ID_LOCOM_COMMAND:
    p_Locom->Command.newCommand = 1;
    p_Locom->Command.commandid = p_Comms->Report.locomCommand.command_id;
    p_Locom->Command.durmsec = p_Comms->Report.locomCommand.duration_ms;
    p_Locom->Command.power = p_Comms->Report.locomCommand.power;
    break;
  }
}
