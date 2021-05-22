/*
 * Audio_Output_Avr.cpp
 *
 * Created: 15/05/2021 06:37:06
 * Author : Nuwan Udara
 */ 

#define F_CPU  1000000UL //problem with proteus simulation, so currenlty using 1MHz F_CPU //#define F_CPU  16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
//input pins
int playbutton=PORTB5;
int changenextsong=PORTB4;
int interruptPin = PORTD2;

void feq_ctc(int step); // the CTC implementation *buggy


//Output pins
int buzzer=PORTB0;

//currently testing multiple methods to generate signals
void feq_ctc(int step){                          // using built in 16bit timer with prescaler 1024 CTC mode.
	TCCR1B = (1 << WGM12); // enable CTC mode
	OCR1A =step;                              // step is the comparison step number
	TIMSK1 = (1 << OCIE1A);					  // set for CTC Mode
	
	sei();									// Call interpupt 
	
	TCCR1B |= (1 << CS12) | (1 << CS10);     // Prescaler 1024
	//{Problem with pulse width and low frequancies not working well}
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PORTB0); // generate square wave 
}



//Local variables
int songnumber=1;

void changesong(){
	_delay_ms(500);
	if (songnumber==3){songnumber=0;}
	else{songnumber++;}
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		
		
    }
}

