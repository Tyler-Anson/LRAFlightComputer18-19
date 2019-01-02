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

//Just sweep making notes between the frequencies 0 and 1500 Hz
void loop() 
{
  tone(BUZZER_PIN, currentTone); // creates a tone at the frequency specified by currentTone in Hz, doesn't shut off until the pin is turned low
  currentTone += incrementor;
  if(currentTone == MIN_TONE || currentTone == MAX_TONE) {incrementor *= -1;} // If we hit one of the ends of our bounds we start incrementing the other way
  delay(10); //will take about two seconds to sweep the full range of notes
}
