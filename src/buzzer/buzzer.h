#include "sensor_interface.hpp"
#include "mqtt.hpp"

class Buzzer : public Sensor, public MQTT
{
public:
	Buzzer(uint16_t serial_number, std::string server_adress, std::string topic, std::string client_ID, uint8_t QoS) : Sensor(serial_number),
		MQTT(server_adress, topic, client_ID, QoS) {}

	void setup() override {};
	void printInfo() override {};
};
