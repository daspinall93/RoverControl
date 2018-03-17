/*
 * gpioLevelTest.cpp
 *
 *  Created on: 8 Mar 2018
 *      Author: G.P Team 1
 */

#define TRIG_PIN 5
#define ECHO_PIN 6

#include <bcm2835.h>
#include

int main()
{
	bcm2835_init();

	flag = 0;

	while(!bcm2835_gpio_lev(ECHO_PIN))
	{
		flag = 1;

	}


	flag = 2;

	return 0;
}




