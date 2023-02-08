#include "SerialMon.h"


// NUR ZUR TESTZWECKEN


void SerialMon::logStr(String dataString) {
	Serial.println(dataString);

}

void SerialMon::setup(int pin) {
  Serial.begin(pin);
}
