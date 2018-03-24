/*
 * old.cpp
 *
 *  Created on: 24 Mar 2018
 *      Author: root
 */

void ManagerModule::GetCmdLineInput()
{
	std::string cmdLineInput;
	size_t pos = 0;

	std::string token;

	/* POLL THE CMD LINE TO SEE IF ANY INPUT WAS PRESENT */
	std::cout << ">>";
	std::cin >> cmdLineInput;

	/* GO THROUGH EACH ELEMENT OF THE COMMAND */
	if ((pos = cmdLineInput.find(" ")) != std::string::npos)
	{
		std::cout << "Only one value allowed" << std::endl;
	}
	else
	{
		token = cmdLineInput.substr(0, pos);

		if (token == "forward")
		{
			/* CURRENTLY ONLY USING THE FORWARD COMMAND WITH NO TIME OR POWER INPUT */
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STRAIGHT_FORWARD;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "backward")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STRAIGHT_BACKWARD;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "right")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_TURN_RIGHT;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "left")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_TURN_LEFT;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "stop")
		{
			MotorCommand.newCommand = 1;
			MotorCommand.commandid = MOTOR_COMMAND_STOP;
			MotorCommand.power_per = PWM_PERCENTAGE;
			MotorCommand.duration_ms = 100000;
		}
		else if (token == "tilt")
		{
			InertCommand.newCommand = 1;
		}
		else if (token == "distance")
		{
			SonarCommand.newCommand = 1;
		}
		else if (token == "end")
		{
			endProgram_flag = 1;
		}
		else
		{
			std::cout << "Incorrect Command" << std::endl;
		}
	}
}

void ManagerModule::ExecuteCommand()
{
	/* CHECK TO SEE IF A NEW COMMAND HAS BEEN ASSIGNED FOR ANY MODULE */
	if (MotorCommand.newCommand)
	{
		p_Motor->Execute(&MotorCommand, &MotorReport);
		MotorCommand.newCommand = 0;
	}
	if (InertCommand.newCommand)
	{
		p_Inert->Execute(&InertReport);
		InertCommand.newCommand = 0;
	}
	if (SonarCommand.newCommand)
	{
		p_Sonar->Execute(&SonarCommand, &SonarReport);
		SonarCommand.newCommand = 0;
	}
}



