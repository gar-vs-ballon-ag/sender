#include "SerialMon.h"

void SerialMon::logStr(String dataString) {
	Serial.println(dataString);

}

void SerialMon::setup(int pin) {
  Serial.begin(pin);
}
