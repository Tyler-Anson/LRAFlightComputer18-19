// Set the programming board to a Mega

#define SERIAL_BAUD 9600

// RTC Includes and Variables
#include <Wire.h>
#include <RTClib.h>

RTC_PCF8523 rtc;
DateTime lastTimeStamp;
DateTime getCurrentTime();

// Timer Includes and Variables
#include <TimerOne.h>
#include <TimerThree.h>

// LSM9DS1 Includes and Variables
#include <Adafruit_LSM9DS1.h>

// GPS Includes and Variables
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#define GPS_BAUD 9600

int arduinoSerialRxPin = 3;                                         // Connect the GPS TX (transmit) pin to Digital 3
int arduinoSerialTxPin = 2;                                         // Connect the GPS RX (receive) pin to Digital 2
SoftwareSerial serialToGPS(arduinoSerialRxPin, arduinoSerialTxPin); 
Adafruit_GPS GPS(&serialToGPS);
bool validLastNmeaStatement;  
void parseAndUpdateGPS();

// End of Includes and Initializations

void setup() 
{
  // Serial Initialization
  Serial.begin(SERIAL_BAUD); 
  
  // RTC Initialization
  rtc.begin();

  // GPS Initialization
  GPS.begin(GPS_BAUD);                            // The GPS always talks at 9600 so we have to tell our fake serial port to talk at 9600 too
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);     // Turns on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);        // Set the update rate to 1 Hz, an go faster but requires more power
  GPS.sendCommand(PGCMD_ANTENNA);                   // Turn on updates about the antennae, not needed
}

void loop() 
{

  // updating current time stamp
  updateCurrentTime();

  // Update the GPS
  if(GPS.newNMEAreceived())
  {
    parseAndUpdateGPS();
  }
  else{GPS.read();}

}

void parseAndUpdateGPS()
{
  char *newStatement = GPS.lastNMEA();
  validLastNmeaStatement = GPS.parse(newStatement);
}

void updateCurrentTime()
{
 lastTimeStamp = rtc.now();
}
