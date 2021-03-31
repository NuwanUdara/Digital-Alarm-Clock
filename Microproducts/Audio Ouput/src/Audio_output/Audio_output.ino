
#include "pitches.h"

int pinIn=13;
int value=0;


int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

int durations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

int songLength = sizeof(melody)/sizeof(melody[0]);
void setup() {
 pinMode(pinIn, INPUT); 
 
}

void loop() {
  value=digitalRead(pinIn);
  if (value==HIGH){
      for (int thisNote = 0; thisNote < songLength; thisNote++){
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
      int duration = 1000/ durations[thisNote];
      tone(8, melody[thisNote], duration);
    // pause between notes
      int pause = duration * 1.3;
      delay(pause);
    // stop the tone
      noTone(8);
      value==LOW;
  }
    
  }


}
