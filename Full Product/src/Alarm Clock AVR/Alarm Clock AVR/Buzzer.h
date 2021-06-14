/*
 * Buzzer.h
 *
 * Created: 14/06/2021 16:34:31
 *  Author: Nuwan Udara
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

/**
When the duration and note frequency are given this will generate 50% duty 
cycle square wave with given frequency for the given duration.
**/
extern void Play_Note(float freq , float dur);

/**
Get the tempo value for the selected Alarm
Input will take the song number and return the assigned tempo
**/
extern int tempochoose(int number);

/**
play function
This will take one input. The song number.
It will take tempo and the chords and duration data from melodies.h accordingly
Using Play_Note it will generate sound
**/
extern void play(int number);

/**
Declare input,output pins and interrupt pin methods
**/
extern void init_buzzer();

#endif /* BUZZER_H_ */