#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include "Sensor.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

class PressureSensor: public Sensor {
  public:
    PressureSensor(long device_interval, String id);
    float getTemp();

    float getPressure();
    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();
    Adafruit_BMP085* bmp;
};

#endif
