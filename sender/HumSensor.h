#ifndef HUMSENSOR_H
#define HUMSENSOR_H

#include "Sensor.h"
#include "DHT.h"

class HumSensor: public Sensor {
  public:
    HumSensor(long device_interval, String id);

    //temperatur und feuchte

    float getTemp();

    float getHum();
    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();

    // dht objekt der DHT Library
    DHT* dht;
};

#endif
