#include "SDcard.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
void SDcard::setup(int pin) {
   if(!SD.begin(pin)){
return;
}
uint8_t cardType = SD.cardType();
if(cardType == CARD_NONE){
return;
}
}
void SDcard::logStr(String dataStr){
File file = SD.open("/log.txt", FILE_APPEND);
if(!file){
return;
}
if(file.print(dataStr)){
file.print("\n");
} else {
}
file.close();
}
