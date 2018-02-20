/*
 * Local.cpp
 *
 *  Created on: 19 Feb 2018
 *      Author: AUser
 */
#include "LocalModule.h"

#include "../MPU6050/MPU6050.h"
#include <math.h>

//MPU6050 object for calling MPU functions
//not a pointer as only contains functions

LocalModule::LocalModule(MPU6050* p_MPU)
{
    /* ASSIGN THE MPU OBJECT POINTER */
    p_AccelGyro = p_MPU;

    /* INITIALISE ALL DATA TO 0 */
    memset(&Report, 0, sizeof(Report));
    memset(&Command, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Config));
    memset(&State, 0, sizeof(State));
}

void LocalModule::Start()
{
    /* ENSURE INITIAL GYRO VALUES ARE 0 */
    State.roll_radGyro = 0;
    State.pitch_radGyro = 0;
    State.yaw_radGyro = 0;

    /* SET PREVIOUS CALL TIME TO CURRENT TIME */
    struct timespec tspec;
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    State.prevCall = round(tspec.tv_nsec / 1.0e6);
    State.prevCall = State.prevCall + (tspec.tv_sec * 1000);
}

void LocalModule::Execute()
{
    /* USE DATA FROM ACCELEROMETER MODULE TO CALCULATE ABSOLUTE PITCH AND ROLL */
    CalculateAnglesAcc();

    /* USE DATA FROM GYRO MODULE TO CALCULATE RELATIVE ROLL */
    CalculateAnglesGyro();

    /* UPDATE THE REPORT STRUCTURE */

}

void LocalModule::CalculateAnglesAcc()
{
    /* CALCULATE ROLL AND PITCH FROM GRAVITY VECTOR */
    State.roll_radAcc = atan2(p_AccelGyro->Report.accY_dig, p_AccelGyro->Report.accZ_dig);
    State.pitch_radAcc = atan(-p_AccelGyro->Report.accX_dig /
			      sqrt(p_AccelGyro->Report.accY_dig * p_AccelGyro->Report.accY_dig + p_AccelGyro->Report.accZ_dig * p_AccelGyro->Report.accZ_dig));
}

void LocalModule::CalculateAnglesGyro()
{
    /* GET THE GYRO RATE */
    State.gyroXRate = p_AccelGyro->Report.accY_dig / 131.0;
    State.gyroYRate = p_AccelGyro->Report.accY_dig / 131.0;
    State.gyroZRate = p_AccelGyro->Report.accY_dig / 131.0;

    /* CALCULATE TIME SINCE LAST CALL */
    struct timespec tspec;
    clock_gettime(CLOCK_MONOTONIC, &tspec);

    State.currentCall = round(tspec.tv_nsec / 1.0e6);
    State.currentCall = State.currentCall + (tspec.tv_sec * 1000);

    /* CALCULATE THE CHANGE IN TIME */
    float deltaTime = (float)(State.currentCall - State.prevCall);

    /* CALCULATE THE CHANGE IN ANGLE */
    /* BE CAREFUL OF NUMERICAL ERRORS HERE */
    State.roll_radGyro += State.gyroXRate * deltaTime;
    State.pitch_radGyro += State.gyroYRate * deltaTime;
    State.pitch_radGyro += State.gyroZRate * deltaTime;

}

void LocalModule::UpdateReport()
{
    Report.pitch_radAcc = State.pitch_radAcc;
    Report.pitch_radGyro = State.pitch_radGyro;
    Report.roll_radAcc = State.roll_radAcc;
    Report.roll_radGyro = State.roll_radGyro;
    Report.yaw_radGyro = State.yaw_radGyro;
}
