#include <TimerOne.h>

#define ledPin 13
#define blinkTime 5000
bool ledOn = false;
void blinkLED();

void setup()
{
  pinMode(ledPin, OUTPUT);

  Timer1.initialize(blinkTime);
  Timer1.attachInterrupt(blinkLED);
  sei();  // allow interrupts 
}

void loop()
{
  ; // we don't need anything in the while loop
}

void blinkLED()
{
  // no ack needed for interrupt
  digitalWrite(ledPin, ledOn);
  ledOn = !ledOn;
}
