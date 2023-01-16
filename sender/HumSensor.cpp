#include "HumSensor.h"

HumSensor::HumSensor(long device_interval, String id) : Sensor(device_interval, id) {
  dht = NULL;

  // DHT22 darf nicht öfter als alle 2,5 s abgefragt werden
  if ( device_interval < 2500 ) setInterval ( 2500 ); 

}

void HumSensor::setup(int pin) {
  dht = new DHT(pin, DHT22);
  dht -> begin();
}



float HumSensor::getTemp() {
  return dht != NULL?dht -> readTemperature(): -999.0;
}

float HumSensor::getHum() {
  return  dht != NULL?dht ->  readHumidity(): -999.0;
}

// s. Sensor.h
String HumSensor::getDataString() {
  return getID() + ":" + String(getTemp()) + ";"+String(getHum());
}

bool HumSensor::action() {
  Serial.println(getDataString());
}
