#include "GPSSensor.h"
#include <sstream>

void GPSSensor::sendUBX(uint8_t * MSG, uint8_t len) {
  int i = 0;
  for (int i = 0; i < len; i++) {
    gpsPort.write(MSG[i]);
    Serial.print(MSG[i], HEX);
  }
  gpsPort.println();
}


boolean GPSSensor::getUBX_ACK(uint8_t * MSG) {
  uint8_t b;
  uint8_t ackByteID = 0;
  uint8_t ackPacket[10];
  unsigned long startTime = millis();
  Serial.print(" * Reading ACK response: ");
  // Construct the expected ACK packet
  ackPacket[0] = 0xB5; // header
  ackPacket[1] = 0x62; // header
  ackPacket[2] = 0x05; // class
  ackPacket[3] = 0x01; // id
  ackPacket[4] = 0x02; // length
  ackPacket[5] = 0x00;
  ackPacket[6] = MSG[2]; // ACK class
  ackPacket[7] = MSG[3]; // ACK id
  ackPacket[8] = 0; // CK_A
  ackPacket[9] = 0; // CK_B
  // Calculate the checksums
  for (uint8_t i = 2; i < 8; i++) {
    ackPacket[8] = ackPacket[8] + ackPacket[i];
    ackPacket[9] = ackPacket[9] + ackPacket[8];
  }
  while (1) {
    // Test for success
    if (ackByteID > 9) {
      // All packets in order!
      Serial.println(" (SUCCESS!)");
      return true;
    }
    // Timeout if no valid response in 3 seconds

    if (millis() - startTime > 3000) {
      Serial.println(" (FAILED!)");
      return false;
    }

    // Make sure data is available to read
    if (gpsPort.available()) {
      b = gpsPort.read();
      // Check that bytes arrive in sequence as per expected ACK packet
      if (b == ackPacket[ackByteID]) {
        ackByteID++;
        Serial.print(b, HEX);
      } else {
        ackByteID = 0; // Reset and look again, invalid order
      }
    }
  }

}

//----------------------------------------------------------------


bool GPSSensor::action() {
  Serial.println(getDataString());
}

GPSSensor::GPSSensor(long device_interval, String id): Sensor(device_interval, id), gps() {
  gps_set_sucess = 0;

  saveString = "GPS:??";
  
  gpsPort.begin(9600);

  while (!gpsPort);
  Serial.println(F("Setting uBlox flight mode: "));

  uint8_t setNav[] = {
    0xB5,
    0x62,
    0x06,
    0x24,
    0x24,
    0x00,
    0xFF,
    0xFF,
    0x06,
    0x03,
    0x00,
    0x00,
    0x00,
    0x00,
    0x10,
    0x27,
    0x00,
    0x00,

    0x05,
    0x00,
    0xFA,
    0x00,
    0xFA,
    0x00,
    0x64,
    0x00,
    0x2C,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,

    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x16,
    0xDC
  };

  while (!gps_set_sucess)
  {
    sendUBX(setNav, sizeof(setNav) / sizeof(uint8_t));
    gps_set_sucess = getUBX_ACK(setNav);
  }
  gps_set_sucess = 0;

  if ( device_interval < 5000 ) setInterval ( 5000 );

  Serial.print( F("NMEAloc.INO: started\n") );
  Serial.print( F("fix object size = ") );
  Serial.println( sizeof(gps.fix()) );
  Serial.print( F("NMEAGPS object size = ") );
  Serial.println( sizeof(gps) );
  Serial.print( F("Looking for GPS device on ") );
  Serial.println( F(GPS_PORT_NAME) );
  Serial.println();
}

String GPSSensor::printL( String prefix, String st, int32_t degE7 ) {

  // Extract and print negative sign
  if (degE7 < 0) {
    degE7 = -degE7;
    st += '-';
  }

  // Whole degrees
  int32_t deg = degE7 / 10000000L;
  st += String( deg );
  st += String( '.' );

  // Get fractional degrees
  degE7 -= deg * 10000000L;
  
  // Print leading zeroes, if needed
  int32_t factor = 1000000L;
  while ((degE7 < factor) && (factor > 1L)) {
    st += String( '0' );
    factor /= 10L;
  }
  
  // Print fractional degrees
  st += String( degE7 );

  return prefix + st;
}


String GPSSensor::GPSdataF( const gps_fix & fix ) {
  String returnString = "";

  if (fix.valid.time) {
    // Set these values to the offset of your timezone from GMT
    static const int32_t zone_hours = 1L; // CET
    static const int32_t zone_minutes = 0L; // usually zero
    static const NeoGPS::clock_t zone_offset = zone_hours * NeoGPS::SECONDS_PER_HOUR + zone_minutes * NeoGPS::SECONDS_PER_MINUTE;
    NeoGPS::time_t localTime( fix.dateTime + zone_offset );
    String hrs = String( localTime.hours );
    if (localTime.hours<10) hrs = "0" + hrs;
    String mins = String( localTime.minutes );
    if (localTime.minutes<10) mins = "0" + mins;
    String seks = String( localTime.seconds );
    if (localTime.seconds<10) seks = "0" + seks;    
    returnString += "t" + hrs + ":" + mins + ":" + seks;
  }

  if (fix.valid.location) {
    if ( fix.dateTime.seconds < 10 ) returnString += String( '0' );
    returnString += String(fix.dateTime.seconds );
    returnString += String( ';' );
    // Serial.print( fix.latitude(), 6 ); // floating-point display
    // Serial.print( fix.latitudeL() ); // integer display
    returnString = printL( "A", returnString, fix.latitudeL() ); // prints int like a float
    returnString += String( ';' );
    // Serial.print( fix.longitude(), 6 ); // floating-point display
    // Serial.print( fix.longitudeL() ); // integer display
    returnString = printL( "O", returnString, fix.longitudeL() ); // prints int like a float
    returnString += String(';' );
    if (fix.valid.satellites) returnString += "S" + String( fix.satellites );
    returnString += String( ";" );
    returnString += "H" + String( gps.fix().altitude_cm());
  }
  else {
    returnString += "?";
  }
  return returnString;
}

String GPSSensor::getDataString() {
  /*
  if (!gps.available(gpsPort)) return "GPS:??";
  else {
    String antwort = "GPS:";
     antwort += GPSdataF( gps.read() );
     return antwort;
  }
  */
 return saveString;
}

void GPSSensor::gpsLoop() {
  if (gps.available( gpsPort ))
    saveString = "GPS:"
    saveString += GPSdataF( gps.read() );
}
