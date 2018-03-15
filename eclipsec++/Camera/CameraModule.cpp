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

#include "pngEncoder/lodepng.h"

void CameraModule::Start()
{

	fileFolder = IMAGE_FOLDER;

	/* SETUP THE CAMERA */
	raspCam.setFormat(raspicam::RASPICAM_FORMAT_RGB);
	raspCam.setWidth(IMAGE_WIDTH);
	raspCam.setHeight(IMAGE_HEIGHT);
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

}

void CameraModule::Execute()
{
	/* CREATE THE DYNAMIC ARRAY FOR HOLDING THE IMAGE DATA */
	unsigned char* data = new unsigned char[raspCam.getImageTypeSize(
			raspicam::RASPICAM_FORMAT_RGB)];

	/* GET CAMERA TO STORE IMAGE IN INTERNAL BUFFER */
	raspCam.grab();

	/* RETRIEVE IMAGE FROM INTERNAL BUFFER AND STORE IN DYNAMIC ARRAY */
	raspCam.retrieve(data, raspicam::RASPICAM_FORMAT_RGB);

	/* ENCODE AND SAVE */
	std::string fileName = fileFolder + "image" + std::to_string(imageNum);

#if IMAGE_PNG_ENCODE
	fileName = fileName + ".png";
	EncodePNG(fileName, data, IMAGE_WIDTH, IMAGE_HEIGHT);
#else
	fileName = fileName + ".ppm";
	EncodePPM(fileName, data, IMAGE_WIDTH, IMAGE_HEIGHT);
#endif

	/* DELETE THE DYNAMIC ARRAY */
	delete[] data;

	/* INCREASE FILE NUMBER */
	imageNum++;

	std::cout << "[CAMERA]Image saved to:" << fileFolder + fileName
			<< std::endl;
}

void CameraModule::EncodePNG(const std::string& fileName, const unsigned char* image,
		unsigned width, unsigned height)
{

	std::vector<unsigned char> png;

	/* ENCODE IMAGE */
	unsigned error = lodepng::encode(png, image, width, height, LCT_RGB, 8);

	/* SAVE IMAGE */
	if (!error)
		lodepng::save_file(png, fileName);

	/* DISPLAY ERRORS */
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

}

void CameraModule::EncodePPM(const std::string& fileName, const unsigned char* image,
		unsigned width, unsigned height)
{
	std::ofstream outFile(fileName);

	/* ENCODE IMAGE AND SAVE */
	outFile << "P6\n" << raspCam.getWidth() << " " << raspCam.getHeight() << " 255\n";
	outFile.write((char*) image, (long) raspCam.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));

	outFile.close();
}

void CameraModule::Stop()
{
	/* STOP CAMERA AND FREE RESOURCES */
	raspCam.release();

}

void CameraModule::Debug()
{

}
