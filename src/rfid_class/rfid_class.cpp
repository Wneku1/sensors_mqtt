#include "rfid_class.hpp"
#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void delay(int ms)
{
#ifdef WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

RFID::RFID(uint16_t serial_number, string server_adress, string topic, string client_ID, uint8_t QoS) : Sensor(serial_number),
	MQTT(server_adress, topic, client_ID, QoS)
{
	mfrc.PCD_Init();
}

void RFID::setup()
{
	mfrc.PCD_Init();
	initClientServerConnection();
}

void RFID::printInfo()
{
	if(!mfrc.PICC_ReadCardSerial())
		return;

	// Print UID
	for(byte i = 0; i < mfrc.uid.size; ++i)
	{
		if(mfrc.uid.uidByte[i] < 0x10)
		{
			printf(" 0");
			printf("%X",mfrc.uid.uidByte[i]);
		}
		else
		{
			printf(" ");
			printf("%X", mfrc.uid.uidByte[i]);
		}

	}
	printf("\n");
}


void RFID::waitForCard()
{
	// Look for a card
	if(!mfrc.PICC_IsNewCardPresent())
		return;

	printInfo();

	delay(1000);
}
