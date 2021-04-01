#include "pitches.h"
#include "melodies.h"

int pinIn=13;
int value=0;
int value2=0;
int pinIn2=12;
int buzzer=8;
int songnumber=1;


int tempo=tempos[songnumber];

int notes = sizeof(melody0[songnumber]) / sizeof(melody0[songnumber][0]) / 2;

int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup() {
   pinMode(pinIn, INPUT);
   pinMode(pinIn2, INPUT);
   
   
  }

void loop() {
  delay(100);
    value=digitalRead(pinIn);
    value2=digitalRead(pinIn2);

    
    if (value==HIGH){
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

          // calculates the duration of each note
          divider = pgm_read_word_near(melody0[songnumber]+thisNote + 1);
          if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
          } 
          else if (divider < 0) {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
           }

           // we only play the note for 90% of the duration, leaving 10% as a pause
           tone(buzzer, pgm_read_word_near(melody0[songnumber]+thisNote), noteDuration * 0.9);

           // Wait for the specief duration before playing the next note.
          delay(noteDuration);

          // stop the waveform generation before the next note.
          noTone(buzzer);
          
          }
          }
          
         //else if (value2==HIGH){
          //delay(1000);
          //if (songnumber==3){
            //songnumber=0;
            //}
          //else{
            //songnumber=songnumber+1;
            //}
            //}
            
            }
