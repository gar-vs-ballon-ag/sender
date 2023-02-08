#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include "Sensor.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

class PressureSensor: public Sensor {
  public:
    PressureSensor(long device_interval, String id);

    // Druck und temperatur

    float getTemp();

    float getPressure();
    String virtual getDataString();
    void virtual setup(int pin);
  private:
    bool virtual action();

    // BMP085 Library (wir verwenden BMP180, geht für mehrere sensoren)
    Adafruit_BMP085* bmp;
};

#endif
