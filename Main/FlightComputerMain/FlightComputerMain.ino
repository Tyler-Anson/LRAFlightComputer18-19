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
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
LSM9DS1 imu;
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW
#define DECLINATION 3.44 // http://www.ngdc.noaa.gov/geomag-web/#declination
float pitch, roll, heading;

// ADXL377 Includes and Definitions
#define SCALE 200
#define ADX_X A0
#define ADX_Y A1
#define ADX_Z A2
float scaledX, scaledY, scaledZ;

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

// RTC Functions
void updateCurrentTime()
{
 lastTimeStamp = rtc.now();
}

// IMU functions
void updateIMUreadings()
{
  // Update the sensor values whenever new data is available
  if ( imu.gyroAvailable() )
  {
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    imu.readMag();
  } 
}

void calculateIMUstate()
{
  roll = atan2(imu.ay, imu.az);
  pitch = atan2(-imu.ax, sqrt(imu.ay * imu.ay + imu.az * imu.az));
  
  if (imu.my == 0)
    heading = (imu.mx < 0) ? PI : 0;
  else
    heading = atan2(imu.mx, imu.my);
    
  heading -= DECLINATION * PI / 180;
  
  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
}

void updateADXreadings()
{
  int rawX = analogRead(ADX_X);
  int rawY = analogRead(ADX_Y);
  int rawZ = analogRead(ADX_Z);

  scaledX = map(rawX, 0, 1023, -SCALE, SCALE); // maps readings from 0 to 5v to -200 to 200 G's 
  scaledY = map(rawY, 0, 1023, -SCALE, SCALE);
  scaledZ = map(rawZ, 0, 1023, -SCALE, SCALE);
}

// GPS Functions
void parseAndUpdateGPS()
{
  char *newStatement = GPS.lastNMEA();
  validLastNmeaStatement = GPS.parse(newStatement);
}
