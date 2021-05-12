/*
 * 2-Evaluation.cpp
 *
 * Created: 5/12/2021 2:30:58 PM
 * Author : Asus
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int key1,key2,i;
void keypad();

int main(void)
{
	while (1)
	{
		keypad();
	}
}

void keypad(){
	DDRD = 0b011111111;   /* Make all pins of PORTD as output pins */
	
	DDRB = 0b01111111;
	PORTB = 0b01111000;
	
	key1 = PINB & 0b00000111;     /*get the pressed key*/
	_delay_us(5);
	
	DDRB = 0b01111111;
	PORTB = 0b00000111;
	
	key2 = PINB & 0b01111000;
	_delay_us(5);
	
	if (key1 == 0b00000100 && key2 == 0b00001000) { PORTD = 0b00100010; }
	if (key1 == 0b00000010 && key2 == 0b00001000) { PORTD = 0b00011111; }
	if (key1 == 0b00000001 && key2 == 0b00001000) { PORTD = 0b00110111; }
	if (key1 == 0b00000100 && key2 == 0b00010000) { PORTD = 0b01100110; }
	if (key1 == 0b00000010 && key2 == 0b00010000) { PORTD = 0b01110101; }
	if (key1 == 0b00000001 && key2 == 0b00010000) { PORTD = 0b01111101; }
	if (key1 == 0b00000100 && key2 == 0b00100000) { PORTD = 0b00100011; }
	if (key1 == 0b00000010 && key2 == 0b00100000) { PORTD = 0b01111111; }
	if (key1 == 0b00000001 && key2 == 0b00100000) { PORTD = 0b01100111; }
	if ((key1 == 0b00000100 || key1 == 0b00000001) && key2 == 0b01000000) {
		PORTD = 0b00000000;
		for(i=0;i<7;i++){
			PORTD |= (1<<i);
		_delay_ms(100);}
	}
	if (key1 == 0b00000010 && key2 == 0b01000000) { PORTD = 0b01111011; }
		
}

