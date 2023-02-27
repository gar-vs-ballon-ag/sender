#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "Sensor.h"

class GasSensor: public Sensor {
  public:

    // der jeweilige Wert des sensors
    float getGas();

    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();

    // dht objekt der DHT Library
    int sensorPin;
};

#endif
