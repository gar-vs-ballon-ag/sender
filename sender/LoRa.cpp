#include "LoRa.h"
#include "settings.h"
#include <SPI.h>
#include <LoRa.h>

#define rst 14
#define dio0 2



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

void Lora::action ( long systime) {
  Serial.println("dsjhgsdkghdgjhsdgjhsdgshgsjdhgsdjhgskdhgsjghsdkjhgdskjhgskjhgshggghjgsjgjjjjjjghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhj");
  Serial.println(systime > lastAction + LORA_INTERVAL);
  Serial.println(systime);
  Serial.println(lastAction);
  Serial.println(LORA_INTERVAL);
  Serial.println("dsjhgsdkghdgjhsdgjhsdgshgsjdhgsdjhgskdhgsjghsdkjhgdskjhgskjhgshggghjgsjgjjjjjjghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhj");
  
  if (systime > lastAction + LORA_INTERVAL ) {
    Serial.println("Sending dsjhgsdkghdgjhsdgjhsdgshgsjdhgsdjhgskdhgsjghsdkjhgdskjhgskjhgshggghjgsjgjjjjjjghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhj");
    LoRa.endPacket();
    LoRa.beginPacket();
    lastAction = systime;
  }
}
