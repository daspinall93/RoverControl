/*
 * CameraStillTest.cpp
 *
 *  Created on: 27 Feb 2018
 *      Author: dan
 */

#include "raspicam.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	raspicam::RaspiCam Camera;

	/* OPEN CAMERA */
	if (!Camera.open())
	{
		printf("Error opening camera");
	}
	sleep(5);

	Camera.grab();

	/* CREATE A DYNAMIC ARRAY TO HOLD DATA */
	unsigned char* data = new unsigned char[Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
	Camera.retrieve(data,raspicam::RASPICAM_FORMAT_RGB);

	FILE *fp;

	fp = fopen("Image1.ppm", "wb");
	fprintf(fp, "P6\n%d %d 255\n", Camera.getWidth(), Camera.getHeight());
	fwrite(data, sizeof(char), Camera.getImageBufferSize(), fp);
	fclose(fp);
	delete data;

	return 0;


}


