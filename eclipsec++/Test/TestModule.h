/*
 * TestModule.h
 *
 *  Created on: 21 Feb 2018
 *      Author: G.P Team 1
 */

#ifndef TEST_TESTMODULE_H_
#define TEST_TESTMODULE_H_

class TestModule
{
public:
	//create the modules to be use and set as friends to access execute and start functions
	LocomModule* p_Locom;
	CommsModule* p_Comms;
	MotorModule* p_Motor1;
	MotorModule* p_Motor2;
	LocalModule* p_Local;
	MPU6050* p_AccelGyro;

	struct
	{

	} Report;

	struct
	{

	} Config;

	TestModule(LocomModule* p_Locom_in, CommsModule* p_Comms_in,
			MotorModule* p_Motor1_in, MotorModule* p_Motor2_in,
			LocalModule* p_Local_in, MPU6050* p_AccelGyro_in);
	void Start();
	void Execute();

private:
	/* PRIVATE DATA MEMBER */
	struct
	{

	} State;

	/*	FUNCTIONS FOR TESTING THE START OF EACH MODULE */
	void TestLocalStart();
	void TestLocomStart();
	void TestCommsStart();
	void TestMotorStart();
	void TestAccelGyroStart();
	//void TestSonarStart();

	/* FUNCTIONS FOR TESTING THE EXECUTION OF EACH MODULE */
	void TestLocalExecute();
	void TestLocomExecute();
	void TestCommsExecute();
	void TestAccelGyroExecute();
	//void TestSonarExecute();



};





#endif /* TEST_TESTMODULE_H_ */
