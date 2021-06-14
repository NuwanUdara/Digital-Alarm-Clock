/*
 * Buzzer.cpp
 *
 * Created: 14/06/2021 16:32:48
 *  Author: Nuwan Udara
 */ 
#define F_CPU  1000000UL //problem with Proteus simulation, so currently using 1MHz F_CPU //#define F_CPU  16000000UL
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__    // This is requaired to make _delay_ms() take vairables
#include <util/delay.h>					// for delay functions
#include <avr/interrupt.h>			   // for clocks and interrupts
#include <avr/pgmspace.h>			  //for PROGMEM
#include "pitches.h"				 // Pitch data is stored in this
#include "melodies.h"				// Chords and duration data and tempo data are stored in here
#include "Buzzer.h"				   // The Include File for the main

 //Buzzer declaration
 #define buzzer_DDR DDRB
 #define buzzer_PORT PORTB
 #define buzzer_PIN PORTB2

 // interrupt button declaration
 #define interruptDDR DDRD
 
 volatile int sp = 1;    // This is a reference to stop the alarm with a button press
 
 void init_buzzer(){
	 // pins ports declaration
	 buzzer_DDR |= _BV(buzzer_PIN) ;			// make buzzer pin output
	 	
	 EICRA |= _BV(ISC01) | _BV(ISC00);		  // set rising edge method
	 EIMSK |= _BV(INT0);					 // enable pin PD1 External interrupt
	 	
	 sei();								   //  this Enables the Global Interrupt Enable (I-bit) in the Status Register (SREG)
	 
 }
 
 void Play_Note(float freq,float dur){
	 // variables
	 long int i,cycles;
	 float half_period,period;
	 
	 if (freq != 0){
		 period=(1/freq)*1000;
		 cycles=dur/period;
		 half_period = period/2;

		 for (i=0;i<cycles;i++)
		 {
			 //50% duty cycle
			 _delay_ms(half_period);
			 buzzer_PORT |= _BV(buzzer_PIN);
			 _delay_ms(half_period);
			 buzzer_PORT &= ~ _BV(buzzer_PIN);
		 }
	 }
	 else {
		 _delay_ms(dur);   // rest
	 }
	 return;
 }
 
 void play(int number){
	 int tempo=tempochoose(number); // choose the right tempo from the list using the function
	 int notes = sizeof(melody0[number])/sizeof(melody0[number][0])/2;
	 int wholenote = (60000 * 2.5) / tempo;
	 int divider = 0;
	 int noteDuration = 0;
	 
	 for (int thisNote = 0; thisNote < notes *2 ; thisNote = thisNote + 2) {
		 if (sp==1){
			 divider = pgm_read_word_near(melody0[number]+thisNote + 1);
			 
			 if (divider > 0) { //positive divider ( positive duration)
				 // it is a regular note
			 noteDuration = (wholenote) / divider;}
			 
			 else if (divider<0){
				 noteDuration=(wholenote)/(divider);// negative durations need to be increased and made positive
				 noteDuration=noteDuration*1.5;
				 noteDuration=-noteDuration;
			 }
			 else if(divider==0){return;} // this will be used to stop playing
			 Play_Note((pgm_read_word_near(melody0[number]+thisNote)), noteDuration*0.9 ); // play the selected pitch
			 _delay_ms(noteDuration*0.5);
		 }
		 else{
			 sp=0;
			 break;
		 }
	 }
 }
 
 /** External interrupt for INT0 (PD2) pin ISR function
 We will use this to stop currently playing melody **/

 ISR (INT0_vect)          //External interrupt Stop button ISR
 {
	 sp=0;
	 _delay_ms(100);
 }

int tempochoose(int number){
	if (number==0){return tempos[0];}
	else if (number==1){return tempos[1];}
	else if (number==2){return tempos[2];}
	else{return tempos[3];}
}