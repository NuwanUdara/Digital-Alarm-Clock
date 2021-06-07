/*
 * 2-Evaluation.cpp
 *
 * Created: 5/12/2021 2:30:58 PM
 * Author : Asus
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "keypad.h"

char keys[4][3] = {{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}} ;
char key;
int i;

int main(void)
{
	DDRD = 0b011111111;   /* Make all pins of PORTD as output pins */
	
	while (1)
	{
		key = getkey(keys);     /*call the function*/
		if (key == '1') { PORTD = 0b00100010; }   /*light up each led s*/
		if (key == '2') { PORTD = 0b00011111; }
		if (key == '3') { PORTD = 0b00110111; }
		if (key == '4') { PORTD = 0b01100110; }
		if (key == '5') { PORTD = 0b01110101; }
		if (key == '6') { PORTD = 0b01111101; }
		if (key == '7') { PORTD = 0b00100011; }
		if (key == '8') { PORTD = 0b01111111; }
		if (key == '9') { PORTD = 0b01100111; }
		if (key == '*' || key =='#'){
			PORTD = 0b00000000;
			for(i=0;i<7;i++){
			PORTD |= (1<<i);
			_delay_ms(100);}
		}
		if (key == '0') { PORTD = 0b01111011; }
	}
}

