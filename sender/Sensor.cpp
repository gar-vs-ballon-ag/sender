#include "Sensor.h"

Sensor::Sensor(long device_interval, String id) {
  lastAction = 0;
  interval = device_interval;
  nameID = id;
}

// wandelt ms zu HH:MM:SS um, aktuell nicht verwendet
String tme (int tme) {
  int hr = tme/3600;                                                        //Number of seconds in an hour
  int mins = (tme-hr*3600)/60;                                              //Remove the number of hours and calculate the minutes.
  int sec = tme-hr*3600-mins*60;                                            //Remove the number of hours and minutes, leaving only seconds.
  String hrMinSec = (String(hr) + ":" + String(mins) + ":" + String(sec));  //Converts to HH:MM:SS string. This can be returned to the calling function.
  return hrMinSec;
}

// siehe Sensor.h, systime ist die zeit die seit start des ESP vergangen ist in ms (s. sender.ino)
String Sensor::checkAction(long systime) {
  // falls es zeit für datenloggen ist
  if (systime - lastAction > interval) {
    lastAction = systime;
    // wird der zu loggende string zurückgegeben (getDataString() s. subklassen)
    return String( systime )+ getDataString();
  }
  else {
    // ansonsten "" zurückgeben, es wir in sender.ino nichts geloggt
    return "";
  }
  
}

String Sensor::getID() {
  return nameID;
}
