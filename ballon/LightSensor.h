#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Sensor.h"

class LightSensor: public Sensor {
  public:
    LightSensor(long device_interval, String id): Sensor(device_interval, id) {}
    int getBrightness();
    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();
    int pdpin;
};

#endif
