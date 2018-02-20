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
#include <stdint.h>

class LocalModule
{
public:
    struct
    {

    } Command;

    struct
    {
	float roll_radAcc;
	float pitch_radAcc;
	float roll_radGyro;
	float pitch_radGyro;
	float yaw_radGyro;
    } Report;

    LocalModule(MPU6050* p_MPU);
    void Start();
    void Execute();

private:
    struct
    {
	/* ANGLES */
	float roll_radAcc;
	float pitch_radAcc;
	float roll_radGyro;
	float pitch_radGyro;
	float yaw_radGyro;

	/* RATES */
	float gyroXRate;
	float gyroYRate;
	float gyroZRate;

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
    void UpdateReport();


};



#endif /* LOCALMODULE_H_ */
