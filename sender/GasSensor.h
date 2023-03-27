#ifndef GASSENSOR_H
#define GASSENSOR_H

#include "Sensor.h"

class GasSensor: public Sensor {
  public:
    GasSensor(long device_interval, String id): Sensor(device_interval, id) {}

    // der jeweilige Wert des sensors
    float getGas();

    String virtual getDataString();
    void virtual setup(int pin);
    int sensorPin;
  private:
    bool virtual action() {};
};

#endif
