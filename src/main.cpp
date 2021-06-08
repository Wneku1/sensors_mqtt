#include "rfid_class.hpp"
#ifndef _WIN32
#include <wiringPi.h>
#endif

#define BUZZERPIN 0

static RFID rfidReader(1, "tcp://192.168.0.39:1235", "alert", "Karta", 1);

int main()
{	
	if(wiringPiSetup() == -1)
	{
		printf("\033[1;31m");
		printf("wiringPi initialization failed !");
		return 1;
	}

	rfidReader.initClientServerConnection();

	while(1)
	{
		rfidReader.waitForCard();
	}
	return 0;
}
