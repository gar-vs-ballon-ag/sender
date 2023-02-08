#include "Logger.h"

class Lora : public Logger {
public:
  void logStr(String dataString);
  void setup(int pin);
private:
  long lastAction;
  void action(long systime);

};
