#include "rfid_class/rfid_class.hpp"

static RFID rfidReader(1);

int main()
{
	while(1)
	{
		rfidReader.waitForCard();
	}
	return 0;
}
