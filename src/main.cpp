#include "rfid_class/rfid_class.hpp"
#ifndef _WIN32
#include <wiringPi.h>
#endif

#define BUZZERPIN 0

static RFID rfidReader(1);

int main()
{
	if(wiringPiSetup() == -1)
	{
		printf("\033[1;31m");
		printf("wiringPi initialization failed !");
		return 1;
	}

	pinMode(BUZZERPIN, OUTPUT);

	while(1)
	{
		rfidReader.waitForCard();
		digitalWrite(BUZZERPIN, HIGH);
		delay(100);
		digitalWrite(BUZZERPIN, LOW);
		delay(100);
	}
	return 0;
}
