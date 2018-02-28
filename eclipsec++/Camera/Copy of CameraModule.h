/*
 * CameraModule.h
 *
 *  Created on: 28 Feb 2018
 *      Author: dan
 */

#ifndef CAMERA_CAMERAMODULE_H_
#define CAMERA_CAMERAMODULE_H_

#include "raspicam/raspicam.h"
#include <string>

class CameraModule
{
public:
	raspicam::RaspiCam raspCam;	//the object's constructor is called here

	void Start();
	void Execute();
	void Stop();

private:
	std::string fileFolder = "/home/pi/SoteriaRover/roverImages/";
	int16_t imageNum;

	void Debug();
};

#endif /* CAMERA_CAMERAMODULE_H_ */
