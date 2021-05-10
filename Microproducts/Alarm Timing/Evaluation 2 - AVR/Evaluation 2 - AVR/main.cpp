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


int main(void)
{
    /* Replace with your application code */
	DDRB = 1<<PORTB0;
    while (1) 
    {
		PORTB = 1<<PORTB0;
    }
}

