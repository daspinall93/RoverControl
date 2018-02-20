/*
 * RoverModule.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: dan
 */
#include "RoverModule.h"

/* INCLUDES FOR TIMING PURPOSES */
#include <math.h>
#include <bcm2835.h>

/* INCLUDED FOR THE COMMAND INTERPRITATION FUNCTION */
#include "../mavlink/v2.0/SoteriaRover/mavlink.h"

/* SELECT WHICH ELEMENTS WILL BE ENABLED */
#define COMMS_ENABLED 1
#define MOTORS_ENABLED 0
#define LOCOM_ENABLED 0
#define LOCAL_ENABLED 0
#define MPU_ENABLED 0

RoverModule::RoverModule(LocomModule* p_Locom_in, CommsModule* p_Comms_in,
			 MotorModule* p_Motor1_in, MotorModule* p_Motor2_in,
			 LocalModule* p_Local_in, MPU6050* p_AccelGyro_in)
{
    /* GET POINTERS TO OTHER MODULES */
    p_Locom = p_Locom_in;
    p_Comms = p_Comms_in;
    p_Motor1 = p_Motor1_in;
    p_Motor2 = p_Motor2_in;
    p_Local = p_Local_in;
    p_AccelGyro = p_AccelGyro_in;

    memset(&Report, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Report));
    memset(&State, 0, sizeof(Report));
    memset(&State.tenhzHighMilSec, 0, sizeof(State.tenhzHighMilSec));

}

void RoverModule::Start()
{
    /* START THE COMMS MODULE */
#if COMMS_ENABLED
    p_Comms->Start();
#endif
    /* NEED TO ENBALE BCM2835 LIBRARY FOR USING PI PINS */
#if MOTORS_ENABLED || LOCAL_ENABLED || MPU_ENABLED
    bcm2835_init();
#endif

#if MPU_ENABLED
    p_AccelGyro->Start();
#endif

#if LOCAL_ENABLED && MPU_ENABLED
    p_Local->Start();
#endif

#if MOTORS_ENABLED
    /* START MOTOR WITH ID=0 */
    p_Motor1->Start(0);

    /* START MOTOR WITH ID=1 */
    p_Motor2->Start(1);
#endif

#if LOCOM_ENABLED && MOTORS_ENABLED
    /* START LOCOM WITH MOTORS 1 & 2 */
    p_Locom->Start();
#endif

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
#if COMMS_ENABLED
//	    p_Comms->Command.newSendCommand = 1;
//	    p_Comms->Command.messageid = MAVLINK_MSG_ID_HEARTBEAT;
//	    p_Comms->Command.heartBeat.Locom_mode = LOCOM_MODE_TURN_LEFT;
	    /* EXECUTE THE COMMS MODULE */
	    p_Comms->Execute();


	    /* TAKE THE COMMANDS RECEIVED AND DISTRIBUTE TO OTHER MODULES INPUTS */
	    if (p_Comms->Report.newPacketReceived)
	    {
		DistributeCommands();
	    }
    #endif
	    Debug();
	}

	/* EXECUTE MODULES AT 10HZ */
	if (State.tenhzFlag)
	{
	      /* EXECUTE THE MPU MODULE */
#if MPU_ENABLED
	      p_AccelGyro->Execute();
#endif

#if LOCAL_ENABLED && MPU_ENABLED

	    /* EXECUTE THE LOCALISATION MODULE */
	    p_Local->Execute();
#endif

#if LOCOM_ENABLED
	    /* EXECUTE THE LOCOMOTION MODULE */
	    p_Locom->Execute();
#endif

#if MOTORS_ENABLED
	    /* EXECUTE BOTH MOTOR MODULES */
	    p_Motor1->Execute();
	    p_Motor2->Execute();
#endif
	}
    }
}

void RoverModule::StartTimer()
{
    /* SET TIME AT WHICH THE ROVER STARTED */
    clock_gettime(CLOCK_MONOTONIC, &State.tspec);

    State.milSec = round(State.tspec.tv_nsec / 1.0e6);
    State.milSec = State.milSec + (State.tspec.tv_sec * 1000);

    /* SET THE REFERENCE TIMES */
    State.tenhzHighMilSec = State.milSec;
    State.onehzHighMilSec = State.milSec;

    /* START FLAGS HIGH */
    State.onehzFlag = 1;
    State.tenhzFlag = 1;

}

void RoverModule::UpdateState()
{
    /* IF HIGH RESET */
    if (State.onehzFlag)
    {
	State.onehzFlag = 0;
    }

    if (State.tenhzFlag)
    {
	State.tenhzFlag = 0;
    }

    /* UPDATE THE TIME */
    clock_gettime(CLOCK_MONOTONIC, &State.tspec);

    State.milSec = round(State.tspec.tv_nsec / 1.0e6);
    State.milSec = State.milSec + (State.tspec.tv_sec * 1000);

    /* SEE IF 10MS HAS PASSED SINCE LAST TIME TENHZ FLAG WAS HIGH */
    long int delta = State.milSec - State.tenhzHighMilSec;
    if (delta > 100)
    {
	/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
	State.tenhzFlag = 1;
	State.tenhzHighMilSec = State.milSec;
    }

    /* SEE IF 100MS HAS PASSED SINCE LAST TIME ONEHZ FLAG WAS HIGH */
    delta = State.milSec - State.onehzHighMilSec;
    if (delta > 1000)
    {
	/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
	State.onehzFlag = 1;
	State.onehzHighMilSec = State.milSec;
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

void RoverModule::Debug()
{
    printf("[ROVER] milSec = %ld \n", State.milSec);
    printf("[ROVER] onehzHigh = %ld \n", State.onehzHighMilSec);
    printf("[ROVER] tenhzHigh = %ld \n", State.tenhzHighMilSec);

}
