#include "GasSensor.h"

void GasSensor::setup(int pin) {
  sensorPin = pin;
}

float getGas() {
  return analogRead(sensorPin);
}

String GasSensor::getDataString() {
  return getID() + ":" + String(getGas());
}
