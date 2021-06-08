#pragma once
#include "sensor_interface.hpp"
#include "MFRC522.h"
#include "mqtt.hpp"

class RFID : public Sensor, public MQTT
{
protected:

public:
	MFRC522 mfrc;
	RFID(uint16_t serial_number, std::string server_adress, std::string topic, std::string client_ID, uint8_t QoS);

	void setup() override;
	void printInfo() override;
	bool isCardAvaiable();
	// virtual void sendStateMsg() = 0; // MQTT
	// virtual void getMsg(void* msg) = 0; // MQTT

	~RFID() {};
};
