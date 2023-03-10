#include "LoRa.h"
#include "settings.h"
#include <SPI.h>
#include <LoRa.h>

#define rst 14
#define dio0 2

/*
* der code aus LoRa::setup und LoRa::logStr wurden aus https://randomnerdtutorials.com/esp32-lora-rfm95-transceiver-arduino-ide/ entnommen
*/

void Lora::setup(int pin) {
  //initialize Serial Monitor
  //Serial.begin(115200);
  //while (!Serial);
  //Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(pin, rst, dio0);
  lastAction = 0;
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  if (!LoRa.begin(866E6)) {
    Serial.println("LoRa Initializing ERROR!");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  //Serial.println("LoRa Initializing OK!");
  Serial.println("Lora begin");
  LoRa.beginPacket();
}

void Lora::logStr( String dataString) {
  LoRa.print(dataString);
  LoRa.print("\n");
}

/*
* Der LoRa-Chip kann die Pakete nicht schnell nacheinander abschicken,
* Also wird das Paket nur alle 5 Sekunden (s. settings.ino) abgeschickt
* und danach ein neues paket eröffnet
*/

void Lora::action ( long systime) {
  
  if (systime > lastAction + LORA_INTERVAL ) {
    LoRa.endPacket();
    LoRa.beginPacket();
    lastAction = systime;
  }
}
