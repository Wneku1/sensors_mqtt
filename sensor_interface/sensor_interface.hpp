#pragma once

/*============================================================================*\
* Includes headers
\*============================================================================*/
#include "stdint.h"


/*============================================================================*\
* Sensor class declarations
\*============================================================================*/

class Sensor
{
	protected:
		uint16_t m_serial_number;

	public:
		constexpr Sensor(uint16_t serial_number) : m_serial_number{serial_number} {};

		virtual uint16_t getSerialNumber() const
		{
			return m_serial_number;
		}

		virtual void setup() = 0;
		virtual void printInfo() = 0;
		// virtual void sendStateMsg() = 0; // MQTT
		// virtual void getMsg(void* msg) = 0; // MQTT

		~Sensor() {};
};
