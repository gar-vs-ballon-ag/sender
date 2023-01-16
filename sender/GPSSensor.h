#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include "Sensor.h"
#include <ARDUINO.h>
#include <TinyGPSPlus.h>

class GPSSensor: public Sensor {
  public:
    GPSSensor(long device_interval, String id);
    void virtual setup(int pin) {}
    String getLong();
    String getLat();
    String getSat();
    String getDataString();
  private:
    bool virtual action();
    TinyGPSPlus* gps;
    String printDateTime(TinyGPSDate &d, TinyGPSTime &t);
    String printFloat(float val, bool valid, int len, int prec);
    String printInt(unsigned long val, bool valid, int len);
};


#endif
