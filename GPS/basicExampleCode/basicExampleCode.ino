#define GPSSerial Serial1 // works only on the mega as the mega has two serial ports


void setup() 
{
  Serial.begin(115200);

  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);
}

     
void loop() {
  if (Serial.available())
  {
    char c = Serial.read();
    GPSSerial.write(c);
  }
  
  if (GPSSerial.available())
  {
    char c = GPSSerial.read();
    Serial.write(c);
  }
}
