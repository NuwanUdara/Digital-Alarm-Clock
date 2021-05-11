/*
 * Evaluation 2 - AVR.cpp
 *
 * Created: 5/8/2021 9:00:23 PM
 * Author : Dakshina Tharidndu
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "ds1307.h"
#include "util/delay.h"


int main(void)
{
    /* Replace with your application code */
	uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t dayofweek = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;
	DDRB = 1<<PORTB0;
	ds1307_init();
	ds1307_setdate(12, 12, 31, 3, 23, 59, 45);
	
    while (1) 
    {
		ds1307_getdate(&year, &month, &day,&dayofweek, &hour, &minute, &second);
		if (second == 50){
			PORTB = 0b00000001;
		}
		else{
			PORTB = 0;
		}
		_delay_ms(1000);	
	}
}

