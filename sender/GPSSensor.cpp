#include "GPSSensor.h"

bool GPSSensor::action() {
  Serial.println(getDataString());
}

GPSSensor::GPSSensor(long device_interval, String id): Sensor(device_interval, id) {
  gps = new TinyGPSPlus();
  if ( device_interval < 5000 ) setInterval ( 5000 ); 
}

String GPSSensor::getDataString() {
  if (getSat() == "**** ") {
    digitalWrite(24, HIGH);
  }
  else {
    digitalWrite(24, LOW);
  }
  return "GPS:" + getSat() + getLat() + getLong() + printDateTime ( gps -> date, gps -> time)+":";
}

String GPSSensor::getLong() {
  return printFloat(gps -> location.lng(), gps -> location.isValid(), 12, 6);
}

String GPSSensor::getLat() {
  return printFloat(gps -> location.lat(), gps -> location.isValid(), 11, 6);
}

String GPSSensor::getSat() {
  return printInt(gps -> satellites.value(), gps -> satellites.isValid(), 5);
}

String GPSSensor::printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  String ret;
  if (!d.isValid())
  {
    ret += F("********** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    ret += sz;
  }
  
  if (!t.isValid())
  {
    ret += F("******** ");
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    ret += sz;
  }
  return ret;
}

String GPSSensor::printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  return sz;
}

String GPSSensor::printFloat(float val, bool valid, int len, int prec)
{
  String ret;
  if (!valid)
  {
    while (len-- > 1)
      ret += ('*');
    ret += (' ');
  }
  else
  {
    ret += (val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      ret += (' ');
  }
  return ret;
}
