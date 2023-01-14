#include "Logger.h"

class Lora : public Logger {
public:
  void logStr(String dataString);
  void setup(int pin);
  void action(long systime);
private:
  long lastAction;  

};
