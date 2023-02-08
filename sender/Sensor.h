#ifndef SENSOR_H
#define SENSOR_H

#include <ARDUINO.h>
#include "device.h"
#include "Logger.h"

class Sensor: public Device {
  public:
    // id = name, wird in der log angezeigt
    Sensor(long device_interval, String id);
    // ruft die daten ab, von den subklassen in folgendem format implementiert: [ID]:[Daten];[Daten], GPS hat eigenes Format für daten
    String virtual getDataString() = 0;
    // überprüft, ob daten geloggt werden
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
