#include <TimerOne.h>
#include <TimerThree.h> // only works for mega

#define ledPin1 13
#define ledPin2 5
#define blinkTime 500000 // in microseconds
#define duty 500 // between 0 and 1024
bool ledOn = false;
void blinkLED();

void setup()
{
  pinMode(ledPin1, OUTPUT);

  Timer1.initialize(blinkTime);
  Timer1.attachInterrupt(blinkLED);
  
  Timer3.pwm(ledPin2, duty); // light up the LED at half brightness
  sei();  // allow interrupts 
}

void loop()
{
  ; // we don't need anything in the while loop
}

void blinkLED()
{
  // no ack needed for interrupt
  cli(); // disable interrupts
  digitalWrite(ledPin1, ledOn);
  ledOn = !ledOn;
  sei(); // re-enable interrupts
}
