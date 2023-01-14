#ifndef HUMSENSOR_H
#define HUMSENSOR_H

#include "Sensor.h"
#include "DHT.h"

class HumSensor: public Sensor {
  public:
    HumSensor(long device_interval, String id);
    float getTemp();

    float getHum();
    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();
    DHT* dht;
};

#endif
