#define BUZZER_PIN 5
//use a PWM pin for the buzzer
//put a 100 ohm resistor between the buzzer pin and the + terminal of the speaker

void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);
}

#define MIN_TONE 0
#define MAX_TONE 1000
int currentTone = 500;
int incrementor = 5;

void loop() 
{
  tone(BUZZER_PIN, currentTone);
  currentTone += incrementor;
  if(currentTone == MIN_TONE || currentTone == MAX_TONE) {incrementor *= -1;}
  delay(10);
}
