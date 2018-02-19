/*
 * Local.cpp
 *
 *  Created on: 19 Feb 2018
 *      Author: AUser
 */
#include "LocalModule.h"

#include "../IMU/I2Cdev/I2Cdev.h"

LocalModule::LocalModule()
{
    /* INITIALISE ALL DATA TO 0 */
    memset(&Report, 0, sizeof(Report));
    memset(&Command, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Config));
    memset(&State, 0, sizeof(State));
}

void LocalModule::Start()
{

}

