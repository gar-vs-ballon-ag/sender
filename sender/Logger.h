#ifndef LOGGER_H
#define LOGGER_H

#include <ARDUINO.h>
#include "device.h"

class Logger: public Device {
  public:
    void virtual logStr(String dataStr) = 0;
    void checkAction(long systime);
    String getID();

  private:
      long lastAction;
      String nameID;
      void virtual action(long systime) = 0;
};

#endif
