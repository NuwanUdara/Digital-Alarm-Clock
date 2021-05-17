/*
 * Audio_Output_Avr.cpp
 *
 * Created: 15/05/2021 06:37:06
 * Author : Nuwan Udara
 */ 

#define F_CPU  16000000UL
#include <avr/io.h>
#include <util/delay.h>

//input pins
int playbutton=PORTB5;
int changenextsong=PORTB4;
int interruptPin = PORTD2;

//Output pins
int buzzer=PORTB0;

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

