// Set the programming board to a Mega

// RTC Includes and Initializations
#include <RTClib.h>

// Timer Includes and Initializations
#include <TimerOne.h>
#include <TimerThree.h>

// LSM9DS1 Includes and Initializations
#include <Adafruit_LSM9DS1.h>

// GPS Includes and Initializations
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

int arduinoSerialRxPin = 3;                                         // Connect the GPS TX (transmit) pin to Digital 3
int arduinoSerialTxPin = 2;                                         // Connect the GPS RX (receive) pin to Digital 2
SoftwareSerial serialToGPS(arduinoSerialRxPin, arduinoSerialTxPin); 
Adafruit_GPS GPS(&serialToGPS);
bool validLastNmeaStatement;  
void parseAndUpdateGPS();

// End of Includes and Initializations

void setup() 
{

  Serial.begin(9600);                         // Telling the serial monitorwe are talking at 9600 bits per second. The faster this is the more power the arduino draws. 9600 is a good base line
  GPS.begin(9600);                            // The GPS always talks at 9600 so we have to tell our fake serial port to talk at 9600 too
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);     // Turns on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);        // Set the update rate to 1 Hz, an go faster but requires more power
  GPS.sendCommand(PGCMD_ANTENNA);                   // Turn on updates about the antennae, not needed

}

void loop() 
{

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
