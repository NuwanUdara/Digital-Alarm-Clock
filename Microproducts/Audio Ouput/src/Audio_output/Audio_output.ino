#include "pitches.h"
#include "melodies.h"

int playbutton=13;
int value=0;
int value2=0;
int changenextsong=12;
int interruptPin = 2;
int buzzer=8;
int songnumber=1;


void setup() {
   pinMode(playbutton, INPUT);
   pinMode(changenextsong, INPUT);
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(interruptPin),playtone , RISING);// Will be used to stop tune from playing
  }

void playtone(){
  tone(8, NOTE_C5, 600);
}

void changesong(){
  delay(500);
  if (songnumber==3){
    songnumber=0;
  }
  
  else{
    songnumber++;
    
    }
    
    }
int tempochoose(int number){
  if (number==0){
    return tempos[0];
    }
   else if (number==1){
    return tempos[1];
    
    }
   else if (number==2){
    return tempos[2];
    }
    else{
      return tempos[3];
      }  
  }

void play(int number){

  int tempo=tempochoose(number);
  int notes = sizeof(melody0[number]) / sizeof(melody0[number][0]) / 2;
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;

  for (int thisNote = 0; thisNote < notes *2 ; thisNote = thisNote + 2) {
    if (digitalRead(interruptPin) == HIGH)
    {
      break;
    }
    // calculates the duration of each note
    divider = pgm_read_word_near(melody0[number]+thisNote + 1);
    
    
    if (divider > 0) {
      // regular note, just proceed
      
      noteDuration = (wholenote) / divider;
      } 
    
    else if (divider < 0) {
      // dotted notes are represented with negative durations
      
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
      }
    else if (divider==0){ //to stop when the useful notes end
      return;
      
      } 
     
      // we only play the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, pgm_read_word_near(melody0[number]+thisNote), noteDuration * 0.9);
 
      // Wait for the specief duration before playing the next note.
      delay(noteDuration);
      
      // stop the waveform generation before the next note.
      noTone(buzzer);
      }
}
void loop() {
  
    value=digitalRead(playbutton);
    value2=digitalRead(changenextsong);
    
    if (value==HIGH){
      tone(buzzer,NOTE_D5,100);
      delay(500);
      play(songnumber);
          }
    if(value2==HIGH){
      tone(buzzer,NOTE_F5 ,100);
      delay(500);
      changesong();
      } 
            }
