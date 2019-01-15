int scale = 200; //can read from -200 to 200 G's

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  // Get raw accelerometer data for each axis
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);

  float scaledX, scaledY, scaledZ;
  scaledX = map(rawX, 0, 1023, -scale, scale); // maps readings from 0 to 5v to -200 to 200 G's 
  scaledY = map(rawY, 0, 1023, -scale, scale);
  scaledZ = map(rawZ, 0, 1023, -scale, scale);

  Serial.println(scaledX);
  Serial.println(scaledY);
  Serial.println(scaledZ);
  delay(500);
}
