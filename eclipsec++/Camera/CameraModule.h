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
#include <stdint.h>
#include <vector>

#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 960
#define IMAGE_BIT_DEPTH

#define IMAGE_FOLDER "/home/pi/SoteriaRover/"

#define IMAGE_PNG_ENCODE 1

class CameraModule
{
public:
	raspicam::RaspiCam raspCam;	//the object's constructor is called here

	void Start();
	void Execute();
	void Stop();

private:
	std::string fileFolder;
	int16_t imageNum;
	void EncodePNG(const std::string& filename, const unsigned char* image,
			unsigned width, unsigned height);
	void EncodePPM(const std::string& filename, const unsigned char* image,
			unsigned width, unsigned height);
	void Debug();
};

#endif /* CAMERA_CAMERAMODULE_H_ */
