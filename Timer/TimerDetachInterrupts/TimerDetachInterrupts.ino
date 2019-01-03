#include <TimerOne.h>

#define ledPin 13
#define blinkTime 500000 // In microseconds
#define MAX_BLINKS 5
int numBlinks = 0;
volatile bool ledOn = false;
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
  numBlinks++;
  if(numBlinks == MAX_BLINKS) {Timer1.detachInterrupt();} //Timer stops running after the number of blinks specified in max blinks
}
