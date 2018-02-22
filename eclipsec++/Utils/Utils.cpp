/*
 * rvUtils.c
 * a set of self-contained functions for the rv project
 *  Created on: 4 Feb 2018
 *      Author: dan
 */

#include "Utils.h"
#include <time.h>
#include <math.h>

long int Utils::GetTimems(){

	struct timespec tspec;	//used to retrieve the current time
	long int timems = 0;
	clock_gettime(CLOCK_MONOTONIC, &tspec);
	tspec.tv_nsec = round(tspec.tv_nsec / 1.0e6);
	timems = tspec.tv_nsec + (tspec.tv_sec * 1000);
	return timems;

}

long int Utils::GetTimeus(){

	struct timespec tspec;	//used to retrieve the current time
	long int timeus = 0;
	clock_gettime(CLOCK_MONOTONIC, &tspec);
	tspec.tv_nsec = round(tspec.tv_nsec / 1.0e3);
	timeus = tspec.tv_nsec + (tspec.tv_sec * 1000);
	return timeus;

}

