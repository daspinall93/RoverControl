/*
 * rvLocal.c
 *
 *  Created on: 4 Feb 2018
 *      Author: dan
 */

#include "rvIMU.h"	//used for interacting with the IMU

//void local_start(){
//
//	local_enable();
//
//}

//void local_do(){
//
//	local_enable
//
//}

//void local_enable(){
//
//	//enable and setup I2C bus for comms with IMU
//	i2c_enable();
//
//	//enable and setup the IMU
//	imu_enable();
//
//	//enable and setup encoders (if available)
//
//
//	//enable and setup sonar device
//
//}

/*
 * Disable the mechanisms for localisation (IMU, sonar, encoders)
 */
//void local_disable(){
//
//	//disable IMU
//	imu_disable();
//
//	//disable I2C
//	i2c_disable();
//
//	//disable encoders (if available)
//
//	//setup sonar device
//
//}

/*
 * Function will use the latest reading from accelerometer to update the roll and pitch of the vehicle
 *
 */
//void local_get_rollpitch(float* roll, float* pitch){
//
//	int16_t acc_raw [3];
//	imu_getAcceleration(acc_raw);
//
//	printf("Accx: %d\t Accy: %d \t Accz: %d \n", acc_raw[0], acc_raw[1], acc_raw[2]);
//
//
//	//calculate roll and pitch from the gravity vector
//	*roll = (float)atan2((float)acc_raw[1], (float)acc_raw[2]);
//	*pitch = (float)atan(-(float)acc_raw[0] / sqrt((float)acc_raw[1] * (float)acc_raw[1] + (float)acc_raw[2] * (float)acc_raw[2]));
//
//	printf("pitch: %f \t roll: %f \n", *roll, *pitch);
//
//}

/*
 * Function will use the latest reading from the gyroscope to integrate
 * over a time period (dt) to estimate the change in yaw position
 *
 */
//void local_update_yaw(float* yaw_est, float dt){
//
//	//prev_yaw will be the yaw accumulated from previous calls to the function
//	int16_t gyro_raw[3];
//	imu_getRotation(gyro_raw);	//get gyroscope values
//
//	printf("Gyrox: %d\t Gyroy: %d \t Gyroz: %d \n", gyro_raw[0], gyro_raw[1], gyro_raw[2]);
//
//	float gyro_z_rate = (float)gyro_raw[2] / 131.0; 	//rate in deg/s
//	gyro_z_rate = (PI/180.0) * gyro_z_rate;	//convert to rad/s
//
//	printf("Gyro_z_rate =  %f", gyro_z_rate);
//
//	//take the rate and integrate (rectangular) over specified time period
//	*yaw_est = *yaw_est + (dt * gyro_z_rate);
//
//	printf("Yaw: %f \n", *yaw_est);
//
//}

