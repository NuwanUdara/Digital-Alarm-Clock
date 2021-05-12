/*
 * 2-Evaluation.cpp
 *
 * Created: 5/12/2021 2:30:58 PM
 * Author : Asus
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xFF;  /* Make all pins of PORTB as output pins */
	
	while (1)     /* Blink PORTB infinitely */
	{
		PORTB = 0x08;
		_delay_ms(500);   /* Delay of 500 Milli second */
		PORTB = 0x00;
		_delay_ms(500);
	}
}

