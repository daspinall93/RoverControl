/*
 * LocalModule.h
 *
 *  Created on: 19 Feb 2018
 *      Author: AUser
 */

#ifndef LOCALMODULE_H_
#define LOCALMODULE_H_

#include "../MPU6050/MPU6050.h"
#include <time.h>

class LocalModule
{
public:
    struct
    {

    } Command;

    struct
    {
	float32_t roll_radAcc;
	float32_t pitch_radAcc;
	float32_t roll_radGyro;
	float32_t pitch_radGyro;
	float32_t yaw_radGyro;
    } Report;

    LocalModule(MPU6050* p_MPU);
    void Start();
    void Execute();

private:
    struct
    {
	/* ANGLES */
	float32_t roll_radAcc;
	float32_t pitch_radAcc;
	float32_t roll_radGyro;
	float32_t pitch_radGyro;
	float32_t yaw_radGyro;

	/* RATES */
	float32_t gyroXRate;
	float32_t gyroYRate;
	float32_t gyroZRate;

	/* TIME */
	long int prevCall;
	long int currentCall;


    } State;

    struct
    {

    } Config;

    MPU6050* p_AccelGyro;

    void CalculateAnglesGyro();
    void CalculateAnglesAcc();


};



#endif /* LOCALMODULE_H_ */
