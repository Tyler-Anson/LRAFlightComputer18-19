#include "notes.h"
#define BUZZER_PIN 5
#define SONG_SIZE 6

int notes[SONG_SIZE] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_D4, NOTE_F4, NOTE_A4};

int durations[6] = {1000, 1000, 1000, 2000, 2000, 2000};
int index = 0;

void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);
  //use a PWM pin for the buzzer
  //put a 100 ohm resistor between the buzzer pin and the + terminal of the speaker
}

//Go through the notes in the array above and play each for their matching durration
void loop() 
{
  tone(BUZZER_PIN, notes[index]);
  delay(durations[index]);
  index = index + 1 % (SONG_SIZE);
}
