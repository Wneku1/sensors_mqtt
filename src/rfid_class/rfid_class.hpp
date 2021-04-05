#pragma once
#include "../../sensor_interface/sensor_interface.hpp"
#include "../../lib/RFID/MFRC522.h"

class RFID : public Sensor
{
protected:
	MFRC522 mfrc;
public:
	RFID(uint16_t serial_number);

	void setup() override;
	void printInfo() override;
	void waitForCard();
	// virtual void sendStateMsg() = 0; // MQTT
	// virtual void getMsg(void* msg) = 0; // MQTT

	~RFID() {};
};
