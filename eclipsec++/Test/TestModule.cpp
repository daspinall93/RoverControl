/*
 * TestModule.cpp
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

TestModule::TestModule(LocomModule* p_Locom_in, CommsModule* p_Comms_in,
			 MotorModule* p_Motor1_in, MotorModule* p_Motor2_in,
			 LocalModule* p_Local_in, MPU6050* p_AccelGyro_in)
{
    /* GET POINTERS TO OTHER MODULES */
    p_Locom = p_Locom_in;
    p_Comms = p_Comms_in;
    p_Motor1 = p_Motor1_in;
    p_Motor2 = p_Motor2_in;
    p_Local = p_Local_in;
    p_AccelGyro = p_AccelGyro_in;

    memset(&Report, 0, sizeof(Report));
    memset(&Config, 0, sizeof(Report));
    memset(&State, 0, sizeof(Report));


}

void TestModule::Start()
{

}

void TestModule::Execute()
{

}

/*	FUNCTIONS FOR TESTING THE START OF EACH MODULE */
void TestModule::TestLocalStart()
{

}

void TestModule::TestLocomStart()
{

}

void TestModule::TestCommsStart()
{

}

void TestModule::TestMotorStart()
{

}

void TestModule::TestAccelGyroStart()
{


}
//void TestSonarStart();

/* FUNCTIONS FOR TESTING THE EXECUTION OF EACH MODULE */
void TestModule::TestLocalExecute()
{

}
void TestModule::TestLocomExecute()
{

}
void TestModule::TestCommsExecute()
{

}
void TestModule::TestAccelGyroExecute()
{

}
//void TestModule::TestSonarExecute()
//{
//
//}
