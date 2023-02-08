#include "PressureSensor.h"

PressureSensor::PressureSensor(long device_interval, String id): Sensor(device_interval, id) {
  bmp = new Adafruit_BMP085();
  if (!bmp -> begin()) {
    // falls keiner gefunden wird
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  }
}

void PressureSensor::setup(int pin) {
  // bleibt leer, kein pin wird benötigt
}



float PressureSensor::getTemp() {
  return bmp != '\0'?bmp -> readTemperature(): -999.0;
}

float PressureSensor::getPressure() {
  return  bmp != '\0'?bmp -> readPressure()/100.0: -999.0;
}

String PressureSensor::getDataString() {
  return getID() + ":" + String(getTemp()) + ";"+String(getPressure());
}

bool PressureSensor::action() {
  Serial.println(getDataString());
}
