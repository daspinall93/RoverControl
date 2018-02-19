/*
 * rv_cam.c
 * Allow access to the Raspberry Pi camera over CSI
 *  Created on: 17 Jan 2018
 *      Author: dan
 */

#include "rvCam.h"

/*
 * Function that creates a new process and runs raspistill
 *
 */



void cam_enable(){

	//currently avoid running as seperate process
//	// create a new process
	int pid = fork();
//
	if (pid != 0) return;
//	// this is the child process running

	// an array of char arrays holding the parameters for raspistill
	char* const args[] = {"raspistill",
			"-q", "50",	// image quality
			"-w", "800", // width
			"-h", "600", // height
			"-hf", "-vf", // flip
			"-t", "1000", // run time
			//"t1", "2000"
			"-s",// wait for process signal	//currently don't run as not using seperate process
			"-n", //no preview
			"-o",  "images/rv_%04d.jpg", NULL}; // default flags/settings for the raspistill program

	// in child process run the command passed to it untill it is ended by passing kill() with any number but SIGUSR1 or SIGUSR2
	execvp(args[0], args);

	printf("Exiting camera process...");

	exit(1);

}

//void cam_take_image(){
//
//	// send a SIGUSR1 to take an image
//	// pid=0 refers to parent process (rv) and child process (raspistill)
//	kill(0, SIGUSR1);	//take image
//
//}
//
//void cam_stop(){
//
//	// take image and stop
//	kill(0, SIGUSR2);
//
//}
