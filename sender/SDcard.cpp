#include "SDcard.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// sd karte initialisieren
void SDcard::setup(int pin) {
   if(!SD.begin(pin)){
return;
}
uint8_t cardType = SD.cardType();
if(cardType == CARD_NONE){
return;
}
}

// daten auf sd karte schreiben
void SDcard::logStr(String dataStr){
  File file = SD.open("/log.txt", FILE_APPEND);
  if(!file){
    return;
  }
  if(file.print(dataStr)){
    // nach jedem eintrag eine neue zeile
    file.print("\n");
  } else {
  }
    file.close();
  }
