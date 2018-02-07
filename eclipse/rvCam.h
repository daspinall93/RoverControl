/*
 * rv_cam.h
 *
 *  Created on: 17 Jan 2018
 *      Author: dan
 */

#ifndef RVCAM_H_
#define RVCAM_H_
#include <stdlib.h>
#include <unistd.h> // provide functions to allow raspstill program to be called
#include <signal.h>
#include <stdio.h>



void cam_enable();
void cam_take_image();
void cam_disable();

#endif /* RVCAM_H_ */
