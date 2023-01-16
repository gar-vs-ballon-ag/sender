#include "LightSensor.h"

void LightSensor::setup(int pin) {
  pinMode(pin, INPUT);
  pdpin = pin;
}


int LightSensor::getBrightness() {
  return analogRead(pdpin);
}

String LightSensor::getDataString() {
  return getID() +":" +String(getBrightness());
}

bool LightSensor::action() {
  Serial.println(getDataString());
}
