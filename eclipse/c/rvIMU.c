/*
 * rv_imu.c
 * Use rv_io to interact with imu (mpu 6050)
 * Adapted from I2Cdev
 *  Created on: 14 Jan 2018
 *      Author: dan
 */

#include "rvIMU.h"




uint8_t buffer[14];


/*
 *
 */
void imu_enable(){

	//enable and set up the imu
	imu_setClockSource(MPU6050_CLOCK_PLL_XGYRO);
	imu_setFullScaleGyroRange(MPU6050_GYRO_FS_250);
	imu_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
	imu_setExternalFrameSync(IMU_EXT_FSYNC_OFF);
	imu_setRate(IMU_SAMPLE_RATE_NODLPF);
	imu_setSleepEnabled(0);

	bcm2835_delay(100);	//allow IMU to turn on
	printf("Test connection to IMU = %d \n", imu_testConnection());

	//calibrate accelerometer and gyroscope
	imu_setAccelOffset(IMU_ACC_XCAL, IMU_ACC_YCAL, IMU_ACC_ZCAL);
	imu_setGyroOffset(IMU_GYR_XCAL, IMU_GYR_YCAL, IMU_GYR_ZCAL);

}

void imu_disable(){

	//put into sleep mode
	imu_setSleepEnabled(1);

}

/*
 *
 */

int8_t imu_testConnection() {

    return imu_getDeviceID() == 0x34;

}

/*
 *
 */
void imu_setClockSource(uint8_t source){

	i2c_writeBits(IMU_ADDR, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);

}

/*
 *
 */
void imu_setFullScaleGyroRange(uint8_t range){

	i2c_writeBits(IMU_ADDR, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);

}

/*
 *
 *
 */
void imu_setFullScaleAccelRange(uint8_t range){

	i2c_writeBits(IMU_ADDR, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);


}

/*
 *
 */
void imu_setSleepEnabled(int8_t enabled){

	i2c_writeBit(IMU_ADDR, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);

}


void imu_setAccelOffset(int16_t x, int16_t y, int16_t z){

	i2c_writeWord(IMU_ADDR, MPU6050_RA_XA_OFFS_H, x);	//x
	i2c_writeWord(IMU_ADDR, MPU6050_RA_YA_OFFS_H, y);	//y
	i2c_writeWord(IMU_ADDR, MPU6050_RA_ZA_OFFS_H, z);	//z

}

void imu_setGyroOffset(int16_t x, int16_t y, int16_t z){

	i2c_writeWord(IMU_ADDR, MPU6050_RA_XG_OFFS_USRH, x);	//x
	i2c_writeWord(IMU_ADDR, MPU6050_RA_YG_OFFS_USRH, y);	//y
	i2c_writeWord(IMU_ADDR, MPU6050_RA_ZG_OFFS_USRH, z);	//z

}

void imu_setRate(uint8_t rate) {
    i2c_writeByte(IMU_ADDR, MPU6050_RA_SMPLRT_DIV, rate);
}

void imu_setExternalFrameSync(uint8_t sync) {
    i2c_writeBits(IMU_ADDR, MPU6050_RA_CONFIG, MPU6050_CFG_EXT_SYNC_SET_BIT, MPU6050_CFG_EXT_SYNC_SET_LENGTH, sync);
}

/*
 *
 */
uint8_t imu_getDeviceID() {
    i2c_readBits(IMU_ADDR, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, buffer);
    return buffer[0];
}

/*
 *
 */
void imu_getAcceleration(int16_t* acc_arr){
	//each accelerometer measurement is 16 bit
	i2c_readBytes(IMU_ADDR, MPU6050_RA_ACCEL_XOUT_H, 6, buffer);
	acc_arr[0] = (((int16_t)buffer[0]) << 8) | buffer[1];
	acc_arr[1] = (((int16_t)buffer[2]) << 8) | buffer[3];
	acc_arr[2] = (((int16_t)buffer[4]) << 8) | buffer[5];

}

/*
 *
 */
void imu_getRotation(int16_t* gyro_arr){
	//each accelerometer measurement is 16 bit
	i2c_readBytes(IMU_ADDR, MPU6050_RA_GYRO_XOUT_H, 6, buffer);
	gyro_arr[0] = (((int16_t)buffer[0]) << 8) | buffer[1];
	gyro_arr[1] = (((int16_t)buffer[2]) << 8) | buffer[3];
	gyro_arr[2] = (((int16_t)buffer[4]) << 8) | buffer[5];

}
