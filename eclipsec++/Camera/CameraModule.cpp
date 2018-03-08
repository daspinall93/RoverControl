/*
 * CameraModule.cpp
 *
 *  Created on: 28 Feb 2018
 *      Author: dan
 */

#include "CameraModule.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bcm2835.h>
#include <stdint.h>

void CameraModule::Start()
{
	/* ASSIGN THE IMAGE FOLDER */
	fileFolder = "/home/pi/SoteriaRover/";

	/* SETUP THE CAMERA */
	raspCam.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	raspCam.setWidth(1280);
	raspCam.setHeight(960);
	raspCam.setHorizontalFlip(0);
	raspCam.setVerticalFlip(1);

	/* OPEN CAMERA */
	if (!raspCam.open())
	{
		std::cout << "Error opening camera" << std::endl;
	}

	/* DELAY TO ALLOW CAMERA TO STARTUP */
	std::cout << "[CAMERA]Starting camera..." << std::endl;
	bcm2835_delay(5000);

//	imageNum = 0;


}

void CameraModule::Execute()
{
	/* CREATE THE DYNAMIC ARRAY FOR HOLDING THE IMAGE DATA */
	unsigned char* data = new unsigned char[raspCam.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];

	/* GET CAMERA TO STORE IMAGE IN INTERNAL BUFFER */
	raspCam.grab();

	/* RETRIEVE IMAGE FROM INTERNAL BUFFER AND STORE IN DYNAMIC ARRAY */
	raspCam.retrieve(data,raspicam::RASPICAM_FORMAT_RGB);

	/* STORE IMAGE IN THE A FILE */
	std::string fileName = "Image" + std::to_string(imageNum) + ".ppm";
	std::ofstream outFile(fileFolder + fileName);
	outFile << "P6\n" << raspCam.getWidth() << " " << raspCam.getHeight() << " 255\n";
	outFile.write((char*) data, (long) raspCam.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));

	/* CLOSE THE FILE */
	outFile.close();

	/* DELETE THE DYNAMIC ARRAY */
	delete[] data;

	/* INCREASE FILE NUMBER */
	imageNum++;

	std::cout << "[CAMERA]Image saved to:" << fileFolder + fileName << std::endl;
}

void CameraModule::Stop()
{
	/* STOP CAMERA AND FREE RESOURCES */
	raspCam.release();

}

void CameraModule::Debug()
{

}
