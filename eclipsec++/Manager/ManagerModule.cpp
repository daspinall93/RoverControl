/*
 * ManagerModule.cpp
 *
 *  Created on: 4 Mar 2018
 *      Author: dan
 */

#include "RoverModule.h"

/* INCLUDES FOR TIMING PURPOSES */
#include <math.h>
#include <bcm2835.h>

/* INCLUDED FOR THE COMMAND INTERPRITATION FUNCTION */
#include "../mavlink/SoteriaRover/mavlink.h"

/* SELECT WHICH ELEMENTS WILL BE ENABLED */
#define COMMS_ENABLED 1
#define MOTORS_ENABLED 1
#define LOCOM_ENABLED 1
#define LOCAL_ENABLED 1
#define MPU_ENABLED 1


void ManagerModule::Start()
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

void ManagerModule::Execute()
{
    while (1)
    {
	/* UPDATE TIMER FLAGS */
	UpdateState();

	/* EXECUTE MODULES AT 1HZ */
	if (onehzFlag)
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
	if (tenhzFlag)
	{
	      /* EXECUTE THE MPU MODULE */
#if MPU_ENABLED
	      p_AccelGyro->Execute();
#endif

#if LOCAL_ENABLED && MPU_ENABLED

	    /* EXECUTE THE LOCALISATION MODULE */
	    p_Local->Execute();
#endifint

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

void ManagerModule::StartTimer()
{
    /* SET TIME AT WHICH THE ROVER STARTED */
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    milSec = round(tspec.tv_nsec / 1.0e6);
    milSec = milSec + (tspec.tv_sec * 1000);

    /* SET THE REFERENCE TIMES */
    tenhzHighMilSec = milSec;
    onehzHighMilSec = milSec;

    /* START FLAGS HIGH */
    onehzFlag = 1;
    tenhzFlag = 1;

}

void ManagerModule::UpdateState()
{
    /* IF HIGH RESET */
    if (onehzFlag)
    {
	onehzFlag = 0;
    }

    if (tenhzFlag)
    {
	tenhzFlag = 0;
    }

    /* UPDATE THE TIME */
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    milSec = round(tspec.tv_nsec / 1.0e6);
    milSec = milSec + (tspec.tv_sec * 1000);

    /* SEE IF 10MS HAS PASSED SINCE LAST TIME TENHZ FLAG WAS HIGH */
    long int delta = milSec - tenhzHighMilSec;
    if (delta > 100)
    {
	/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
	tenhzFlag = 1;
	tenhzHighMilSec = milSec;
    }

    /* SEE IF 100MS HAS PASSED SINCE LAST TIME ONEHZ FLAG WAS HIGH */
    delta = milSec - onehzHighMilSec;
    if (delta > 1000)
    {
	/* SET FLAG HIGH AND SET TIME AT WHICH FLAG WENT HIGH */
	onehzFlag = 1;
	onehzHighMilSec = milSec;
    }

}

void ManagerModule::DistributeCommands()
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

void ManagerModule::Debug()
{
    printf("[ROVER] milSec = %ld \n", milSec);
    printf("[ROVER] onehzHigh = %ld \n", onehzHighMilSec);
    printf("[ROVER] tenhzHigh = %ld \n", tenhzHighMilSec);

}



