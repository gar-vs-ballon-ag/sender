#include "LightSensor.h"

void LightSensor::setup(int pin) {
  pinMode(pin, INPUT);
  pdpin = pin;
}


int LightSensor::getBrightness() {
  // ganz normales analogRead
  return analogRead(pdpin);
}

//s. Sensor.h
String LightSensor::getDataString() {
  return getID() +":" +String(getBrightness());
}

bool LightSensor::action() {
  Serial.println(getDataString());
}
