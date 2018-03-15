/*
 * CameraStillTest.cpp
 *
 *  Created on: 27 Feb 2018
 *      Author: dan
 */

#include  "CameraModule.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	CameraModule Camera = CameraModule();

	/* START THE CAMERA */
	Camera.Start();

	/* WAIT FOR CAMERA TO STABILISE */
	sleep(5);

	/* CAPTURE IMAGE */
	Camera.Execute();

	sleep(10);

	Camera.Execute();

	/* RELEASE THE CAMERA */
	Camera.Stop();

}


