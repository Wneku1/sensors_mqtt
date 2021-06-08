#include "rfid_class.hpp"
#ifndef _WIN32
#include <wiringPi.h>
#endif

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "buzzer/buzzer.h"

#define BUZZERPIN 0

static RFID rfidReader(1, "tcp://192.168.0.39:1235", "RFIDCard", "Karta", 1);

static Buzzer buzzer(2, "tcp://192.168.0.39:1235", "alert", "buzzer", 1);

static uint8_t card1[] {0x27, 0x2E, 0x1B, 0xB3};
static MFRC522::Uid card2;

const string wrapMsg(string msg)
{
	string addVal = msg;
	addVal.append("\"}");
	string json = "{\"AuthToken\":\"TEST\", \"MqttType\":\"Publisher\", \"Device\":{\"Type\":\"TempSens\", \"Topic\":\"RFIDCard\", \"View\":\"text\"}, \"Value\":\"";
	json.append(addVal);
	return json;
}
void pushBuzzer(bool isOn)
{
	const string onOff(isOn ? "on" : "off");
	buzzer.pushStatus(onOff);
}

int main()
{	
	if(wiringPiSetup() == -1)
	{
		printf("\033[1;31m");
		printf("wiringPi initialization failed !");
		return 1;
	}

	buzzer.initClientServerConnection();
	rfidReader.initClientServerConnection();

	while(1)
	{
		if(rfidReader.isCardAvaiable())
		{
			bool isOk = true;
			for(int i = 0; i < rfidReader.mfrc.uid.size; i++)
			{
				if(card1[i] != rfidReader.mfrc.uid.uidByte[i])
					isOk = false;
			}

			if(isOk)
			{
				const string mm(wrapMsg("OTWORZ DRZWI"));
				rfidReader.pushStatus(mm);
			}
			else
			{
				pushBuzzer(true);
			}
		}

	}
	return 0;
}
