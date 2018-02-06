/*
 * rv.c
 *
 *  Created on: 14 Jan 2018
 *      Author: dan
 */

//Fucntions I haven't created
//#include <unistd.h> // provide functions to allow raspstill program to be called
#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <sched.h>
//#include <sys/mman.h>
#include <bcm2835.h>
//#include <time.h>

//Functions I've created
#include "rvLocom.h"
#include "rvUtils.h"
//#include "rvLocal.h
//#include "rvCam.h"
//#include "rvCom.h"

//data for locom
locom_comConfStruct locom_comConf;
locom_statRepStruct locom_statRep;

//private functions
void main_start();
void main_testLocom();
void main_stop();


int main(){

	main_start();

	main_testLocom();

	main_stop();

	return 1;

}

void main_start(){

	//initlialise the bcm2835 library to allocate memory
	printf("Initialisation of BCM library = %d \n", bcm2835_init());

	//setup the modules
	//startup the main I/O of the system
	printf("Enabling and setting up locomotion module... \n");
	//set locom_modConf

	locom_start();

}

void main_stop(){

	//startup the main I/O of the system
	printf("Disabling locomotion functions... \n");
	locom_stop();

	//close the library to release allocated memory
	printf("Closing of BCM library = %d \n",bcm2835_close());

}

void main_testLocom(){

	//generate the command
	locom_comConf.newCommand = 1;	//new command being applied
	locom_comConf.msecDur = 6000;	//command duration
	locom_comConf.command = LOCOM_COMMAND_STRAIGHT_FORWARD;
	locom_comConf.power = 100;

	while(locom_statRep.comElapsedTimems < 3000){
		locom_do(&locom_comConf, &locom_statRep);
		bcm2835_delay(1000);
	}

	//generate new command
	locom_comConf.newCommand = 1;	//new command being applied
	locom_comConf.command = LOCOM_COMMAND_STOP;
	locom_comConf.msecDur = 2000;
	locom_comConf.power = 0;

	locom_do(&locom_comConf, &locom_statRep);
	bcm2835_delay(1000);

	locom_do(&locom_comConf, &locom_statRep);

	locom_comConf.newCommand = 1;	//new command being applied
	locom_comConf.command = LOCOM_COMMAND_TURN_LEFT;
	locom_comConf.msecDur = 2000;

	locom_do(&locom_comConf, &locom_statRep);

	bcm2835_delay(500);
	locom_do(&locom_comConf, &locom_statRep);

	locom_comConf.newCommand = 1;	//new command being applied
	locom_comConf.command = LOCOM_COMMAND_STOP;
	locom_comConf.msecDur = 2000;
}

//void test_loc(){
//
//	float roll, pitch, yaw;
//	roll = 0.0;
//	pitch = 0.0;
//	yaw = 0.0;
//
//	// test localisation functions
//	for (int i = 0; i < 10; i++){
//		local_get_rollpitch(&roll, &pitch);
//		bcm2835_delay(1000);
//
//	}
//
//	for (int i = 0; i < 10; i++){
//		local_update_yaw(&yaw, 100);
//		bcm2835_delay(1000);
//
//	}
//
//
//
//}

//void test_cam(){
//
//	//TODO sort out what to do about camera
//	cam_enable();
//
//	sleep(5);
//
//	cam_start();
//
//	sleep(1);
//
//	cam_start();
//
//}

//void test_com(){
//
//	com_enable();
//
//	sleep(5);
//
//	char message[256] = "004.023.100";
//
//	com_send(message);
//
//	printf("Here");
//	//wait for message to be sent
//	sleep(5);
//
//	bzero(message, 256);
//	com_recieve(message);
//	printf("%s", message);
//
//}

//void test_timings(){
//
//	struct sched_param sp;
//	memset(&sp, 0, sizeof(sp));
//	sp.__sched_priority = sched_get_priority_max(SCHED_FIFO);
//	sched_setscheduler(0, SCHED_FIFO, &sp);
//	mlockall(MCL_CURRENT|MCL_FUTURE);
//
//	//use bcm2835 delay (not sure which timer is used
//	struct timespec tspec = {0,0};
//
//	int i = 0;
//	while (i <= 10){
//		clock_gettime(CLOCK_MONOTONIC, &tspec);
//		tspec.tv_nsec = round(tspec.tv_nsec / 1.0e6);
//
//		printf("Current s = %ld \n", tspec.tv_sec);
//
//		printf("Current ms = %ld \n",tspec.tv_nsec);
//
//		printf("i = %d \n", i);
//		bcm2835_delay(1000);
//		i++;
//
//	}
//
//	//using the clock_gettime which uses the system timer counter (lower 32 bits)
//	i = 0;
//
//
//
//
//}
