#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include "Sensor.h"
#include <ARDUINO.h>
#include <NMEAGPS.h>

class GPSSensor: public Sensor {
  public:
    GPSSensor(long device_interval, String id);
    void virtual setup(int pin) {}
    String getDataString();
    void gpsLoop();
  private:
    bool virtual action();
    NMEAGPS gps; // This parses the GPS characters
    byte gps_set_sucess;
    String GPSdataF(const gps_fix & fix);
    boolean getUBX_ACK(uint8_t * MSG);
    void sendUBX(uint8_t * MSG, uint8_t len);
    String printL( String prefix, String st, int32_t degE7 );
    String saveString;
};


#define gpsPort Serial2

#define GPS_PORT_NAME "Serial2"

#define DEBUG_PORT Serial

#define LED_BUILTIN 4

//------------------------------------------------------------

// Check that the config files are set up properly

#if!defined(NMEAGPS_PARSE_RMC)

#error You must uncomment NMEAGPS_PARSE_RMC in NMEAGPS_cfg.h!

  #endif

#if!defined(GPS_FIX_TIME)

#error You must uncomment GPS_FIX_TIME in GPSfix_cfg.h!

  #endif

#if!defined(GPS_FIX_LOCATION)

#error You must uncomment GPS_FIX_LOCATION in GPSfix_cfg.h!

  #endif

#if!defined(GPS_FIX_SPEED)

#error You must uncomment GPS_FIX_SPEED in GPSfix_cfg.h!

  #endif

#if!defined(GPS_FIX_SATELLITES)

#error You must uncomment GPS_FIX_SATELLITES in GPSfix_cfg.h!

  #endif

#ifdef NMEAGPS_INTERRUPT_PROCESSING

#error You must * NOT * define NMEAGPS_INTERRUPT_PROCESSING in NMEAGPS_cfg.h!

  #endif

#ifndef GPS_FIX_ALTITUDE

#error GPS_FIX_ALTITUDE must be defined in GPSfix_cfg.h!

  #endif


#endif
