#ifndef LOGGER_H
#define LOGGER_H

#include <ARDUINO.h>
#include "device.h"

class Logger: public Device {
  public:
    // Loggen von daten
    void virtual logStr(String dataStr) = 0;
    // LoRa schickt die daten als paket alle 5000 ms
    void checkAction(long systime);
    String getID();

  private:
      long lastAction;
      String nameID;
      // von subklassen implementiert
      void virtual action(long systime) = 0;
};

#endif
