#define BUZZER_PIN 5
//use a PWM pin for the buzzer
//put a 100 ohm resistor between the buzzer pin and the + terminal of the speaker

void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() 
{
  analogWrite(BUZZER_PIN, 120);
}
