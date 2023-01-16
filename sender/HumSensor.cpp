#include "HumSensor.h"

HumSensor::HumSensor(long device_interval, String id) : Sensor(device_interval, id) {
  dht = '\0';
  if ( device_interval < 2500 ) setInterval ( 2500 ); 

}

void HumSensor::setup(int pin) {
  dht = new DHT(pin, DHT22);
  dht -> begin();
}



float HumSensor::getTemp() {
  return dht != '\0'?dht -> readTemperature(): -999.0;
}

float HumSensor::getHum() {
  return  dht != '\0'?dht ->  readHumidity(): -999.0;
}

String HumSensor::getDataString() {
  return getID() + ":" + String(getTemp()) + ";"+String(getHum());
}

bool HumSensor::action() {
  Serial.println(getDataString());
}
