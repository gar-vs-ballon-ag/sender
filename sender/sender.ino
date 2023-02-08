/*
****************************
* HAUPTPROGRAMM
* Alle Konstanten sind in settings.h zu finden.
****************************
*/


#include "settings.h"

#include "LightSensor.h"
#include "PressureSensor.h"
#include "HumSensor.h"
#include "GPSSensor.h"
#include "SerialMon.h"
#include "Logger.h"
#include "SDcard.h"
#include "LoRa.h"

//Arrays der Logger und Sensoren initialisieren 
Sensor* sensors [SENSOR_NUMBER];
Logger* loggers [LOGGER_NUMBER];
GPSSensor* gpsSensor;

void setup() {
  // Kontroll-LED initialisieren
  pinMode(24, OUTPUT);
  
  // Logger und Sensor Array mit NULL füllen
  
  for ( int i =0 ; i < LOGGER_NUMBER; i++) {
    loggers[i] = NULL;
  }
  
  for ( int i =0 ; i < SENSOR_NUMBER; i++) {
    sensors[i] = NULL;
  }
  
  // Alles initialisieren
  
  // Serieller Monitor als Logger-Klasse, nur zu Testzwecken.
  loggers[0] = new SerialMon();
  loggers[0] -> setup(115200);

  loggers[1] = new SDcard();
  loggers[1] -> setup(15);

  loggers[2] = new Lora();
  loggers[2] -> setup(LORA_ss);
  
  
  sensors[0] = new LightSensor(5000, "L_FULL");
  sensors[0] -> setup(PDALL);
  
  sensors[1] = new PressureSensor(5000, "BAR");
  
  sensors[2] = new HumSensor(5000, "F2");
  sensors[2] -> setup(DHTPIN1);

  sensors[3] = new HumSensor(5000, "F1");
  sensors[3] -> setup(DHTPIN2);
  
  sensors[4] = new LightSensor(5000, "LR");
  sensors[4] -> setup(PDRED);
  
  sensors[5] = new LightSensor(5000, "LB");
  sensors[5] -> setup(PDBLUE);


  sensors[6] = new LightSensor(5000, "LG");
  sensors[6] -> setup(PDGREEN);

  gpsSensor = new GPSSensor(5000, "GPS");
  sensors[7] = gpsSensor;

  loggers[0] -> logStr("Setup abgeschlossen!");

}

void loop() {
  long systime = millis();
  // durch alle sensoren durchloopen
  for ( int i =0 ; i < SENSOR_NUMBER; i++) {
    // den sensor seine aktion ausführen lassen -> falls es noch nicht zeit dazu ist, gibt es "" zurück, ansonsten den zu loggenden string
    String ret = sensors[i] -> checkAction(systime);
    // falls was zurückgegeben, über die logger drüberloopen
    if (ret != "") {
      for(int i = 0  ; i < LOGGER_NUMBER ; i++) {
        // den string loggen
        loggers[i] -> logStr(ret);
      }
    }
  }

 // extra prüfen, ob es zeit ist ein LoRa paket zu senden
 loggers[2] -> checkAction(systime);

 gpsSensor -> gpsLoop();
 
 //delay, um strom zu sparen
 // delay(2500); 
}
