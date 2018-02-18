/*
 * RoverModule.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: dan
 */
#include "RoverModule.h"

void RoverModule::Start()
{
    /* START THE COMMS MODULE */
    Comms.Start();

    /* START THE TIMER MODULE */
    Timer.Start();

    /* START MOTOR WITH ID=0 */
    Motor1.Start(0);

    /* START MOTOR WITH ID=1 */
    Motor2.Start(1);

    /* START LOCOM WITH MOTORS 1 & 2 */
    Locom.Start(&Motor1, &Motor2);

}

void RoverModule::Execute()
{
    while (1)
    {
	/* EXECUTE TIMER TO UPDATE FLAGS */
	Timer.Execute();

	/* EXECUTE MODULES AT 1HZ */
	if (Timer.Report.onehzFlag)
	{

	}

	/* EXECUTE MODULES AT 10HZ */
	if (Timer.Report.tenhzFlag)
	{
	    /* EXECUTE THE COMMS MODULE */
	    Comms.Execute();

	    /* EXECUTE THE LOCALISATION MODULE */
	    //Local.Execute();

	    /* EXECUTE THE LOCOMOTION MODULE */
	    Locom.Execute();

	    /* EXECUTE BOTH MOTOR MODULES */
	    Motor1.Execute();
	    Motor2.Execute();

	}

    }
}
