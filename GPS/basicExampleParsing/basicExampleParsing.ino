#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Remember that the TX of the GPS has to be connected to the RX of the Arduino, and vice versa.
// This is because the GPS talks on TX and spits it out into the RX of the Arduino, and the Arduino can do the same with it's TX to the GPS RX
int arduinoSerialRxPin = 3;                                         // Connect the GPS TX (transmit) pin to Digital 3
int arduinoSerialTxPin = 2;                                         // Connect the GPS RX (receive) pin to Digital 2
SoftwareSerial serialToGPS(arduinoSerialRxPin, arduinoSerialTxPin); // We are telling the arduino we want to make a fake a serial port using the pins 3(Arduino RX) and 2(Arduino TX)
Adafruit_GPS GPS(&serialToGPS);                                     // To initialize the GPS we have to tell it what serial port to talk on, it will use this to grab NEMA statements

// This runs once when the arduino starts up
void setup()
{
  Serial.begin(9600);                         // Telling the serial monitorwe are talking at 9600 bits per second. The faster this is the more power the arduino draws. 9600 is a good base line
  GPS.begin(9600);                            // The GPS always talks at 9600 so we have to tell our fake serial port to talk at 9600 too
  
  // This initialization stuff is straight from their example code, you don't ever have to know this
  Serial.println("Initializing GPS..");
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);     // Turns on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);        // Set the update rate to 1 Hz, an go faster but requires more power
  GPS.sendCommand(PGCMD_ANTENNA);                   // Turn on updates about the antennae, not needed
  Serial.println("GPS initialized!");
  
  Serial.println("Starting test..");
}

void loop()
{
  if(GPS.newNMEAreceived())                                    // GPS.newNMEAreceived returns true if there is a new message from the GPS, these messages are called NMEA statements
  {
      char *newStatement = GPS.lastNMEA();                     // This gives us a string of the last message received from the GPS
      bool wasGoodNemaStatement = GPS.parse(newStatement);     // This breakes up the string into values like latitude and longitude and stores them inside GPS so we can access them later
      if(wasGoodNemaStatement == false)                        // GPS.parse() returns a true if it was given a good NMEA statement, we have to check if we got a bad one so we don't use bad GPS data
      {
        Serial.println("We got a bad NEMA statement, waiting for the next one..\n\n");
      }
      else
      {
        Serial.println("Successfully parsed the NEMA statement, here are the results: ");

        // GPS has several variables inside of it that store the last updated coordinates, fix, time, and even date of our GPS module. Fix is the number of satelites the GPS is talking too. The more the better.
        // Every time we parse a NMEA statement all these variables inside GPS are updated. 
        Serial.print("Latitude: ");
        Serial.println(GPS.latitude);
        Serial.print("Longitude: ");
        
        Serial.println(GPS.longitude);
        Serial.print("Fix: ");
        
        Serial.println(GPS.fix);
        Serial.println("\n\n");       //Printing some new lines to give us space between each reading on the monitor for readability
      }
      
  }
  else{GPS.read();}
}
