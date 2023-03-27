#include "GasSensor.h"

void GasSensor::setup(int pin) {
  sensorPin = pin;
}

float GasSensor::getGas() {
  return analogRead(sensorPin);
}

String GasSensor::getDataString() {
  return getID() + ":" + String(getGas());
}
