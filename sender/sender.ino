#include "settings.h"

#include "LightSensor.h"
#include "PressureSensor.h"
#include "HumSensor.h"
#include "GPSSensor.h"
#include "SerialMon.h"
#include "Logger.h"
#include "SDcard.h"

Sensor* sensors [SENSOR_NUMBER];
Logger* loggers [LOGGER_NUMBER];

void setup() {
  for ( int i =0 ; i < LOGGER_NUMBER; i++) {
    loggers[i] = '\0';
  }
  
  for ( int i =0 ; i < SENSOR_NUMBER; i++) {
    sensors[i] = '\0';
  }


  loggers[0] = new SerialMon();
  loggers[0] -> setup(115200);

  loggers[1] = new SDcard();
  loggers[1] -> setup(15);
  
  
  sensors[0] = new LightSensor(1000, "Licht_Ganz");
  sensors[0] -> setup(PDALL);
  
  //sensors[1] = new PressureSensor(5000, "Druck");
  sensors[1] = new LightSensor(1000, "Licht_Blau");
  
  sensors[2] = new HumSensor(1000, "Feuchte_2_27");
  sensors[2] -> setup(DHTPIN1);

  sensors[3] = new HumSensor(5000, "Feuchte_1_26");
  sensors[3] -> setup(DHTPIN2);
  
  sensors[4] = new LightSensor(1000, "Licht_Rot");
  sensors[4] -> setup(PDRED);
  
  sensors[5] = new LightSensor(1000, "Licht_Blau");
  sensors[5] -> setup(PDBLUE);


  sensors[6] = new LightSensor(1000, "Licht_Grün");
  sensors[6] -> setup(PDGREEN);

  sensors[7] = new GPSSensor(5000, "GPS");
  ss.begin(GPSBAUD, SERIAL_8N1, DHTPIN1, DHTPIN2);

  loggers[0] -> logStr("Setup abgeschlossen!");

}

void loop() {
  long systime = millis();
  for ( int i =0 ; i < SENSOR_NUMBER; i++) {
    String ret = sensors[i] -> checkAction(systime);
    if (ret != "") {
      for(int i = 0  ; i < LOGGER_NUMBER ; i++) {
        loggers[i] -> logStr(ret);
      }
    }
  }
 delay(999); 
}
