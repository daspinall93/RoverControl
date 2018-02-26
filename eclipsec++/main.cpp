/*
 * main.cpp
 *
 *  Created on: 9 Feb 2018
 *      Author: dan
 */

#include "Rover/RoverModule.h"
#include "Locom/LocomModule.h"
#include "Comms/CommsModule.h"
#include "Inert/InertModule.h"
#include "Motor/MotorModule.h"
#include "Local/LocalModule.h"

int main()
{
    /* INITIALISE THE MODULES (OBJECTS) */
    //not currently dynamically allocated (new)
    CommsModule Comms;

    /* CREATE MOTOR OBJECTS AND ALLOW LOCOM TO ACCESS THEM */
    MotorModule Motor1;
    MotorModule Motor2;
    LocomModule Locom(&Motor1, &Motor2);

    /* CREATE MPU OBJECT AND ALLOW LOCAL MODULE TO ACCESS IT */
    MPU6050 AccelGyro;
    LocalModule Local(&AccelGyro);
    RoverModule Rover(&Locom, &Comms, &Motor1, &Motor2, &Local, &AccelGyro);

    /* START ROVER MODULE AND PASS POINTERS TO EACH MODULE */
    Rover.Start();

    /* EXECUTE ROVER MODULE   */
    Rover.Execute();

    return 0;
}
