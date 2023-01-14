#include "Sensor.h"

Sensor::Sensor(long device_interval, String id) {
  lastAction = 0;
  interval = device_interval;
  nameID = id;
}

String tme (int tme) {
  int hr = tme/3600;                                                        //Number of seconds in an hour
  int mins = (tme-hr*3600)/60;                                              //Remove the number of hours and calculate the minutes.
  int sec = tme-hr*3600-mins*60;                                            //Remove the number of hours and minutes, leaving only seconds.
  String hrMinSec = (String(hr) + ":" + String(mins) + ":" + String(sec));  //Converts to HH:MM:SS string. This can be returned to the calling function.
  return hrMinSec;
}

String Sensor::checkAction(long systime) {
  
  if (systime - lastAction > interval) {
    lastAction = systime;
    return String( systime )+ getDataString() + tme(systime);
  }
  else {
    return "";
  }
  
}

String Sensor::getID() {
  return nameID;
}
