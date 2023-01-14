#ifndef SENSOR_H
#define SENSOR_H

#include <ARDUINO.h>
#include "device.h"
#include "Logger.h"

class Sensor: public Device {
  public:
    Sensor(long device_interval, String id);
    String virtual getDataString() = 0;
    String checkAction(long systime);
    String getID();
    
  private:
    long lastAction;
    long interval;
    String nameID;
  protected:
    bool virtual action() = 0;
    void setInterval(long i) { if ( i > 0 ) interval = i; }
  
};

#endif
