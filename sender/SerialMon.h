#include "Logger.h"

class SerialMon : public Logger {
public:
	void logStr(String dataString);
  void setup(int pin);
private:
  void action(long systime){}
};
