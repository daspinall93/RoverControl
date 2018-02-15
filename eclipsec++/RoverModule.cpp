/*
 * RoverModule.cpp
 *
 *  Created on: 14 Feb 2018
 *      Author: dan
 */
#include "RoverModule.h"

void RoverModule::Start()
{
	Motor1.Start(0);
	Motor2.Start(1);
	Locom.Start(&Motor1, &Motor2);
	Comms.Start();
	Timer.Start();
}

void RoverModule::Execute()
{
	while (1){
		Timer.Execute();

		if (Timer.Report.onehzFlag)
		{

		}

		if (Timer.Report.tenhzFlag)
		{
			/* Call comms to check on any new commands and pass telemetry */
			Comms.Execute();

			/* Call local to update state of the rover */
			//Local.Execute();

			/* Call Locom to implement the new commands */
			Locom.Execute();

			/* Call motors to execute any new commands from locom */
			Motor1.Execute();
			Motor2.Execute();

		}

}
