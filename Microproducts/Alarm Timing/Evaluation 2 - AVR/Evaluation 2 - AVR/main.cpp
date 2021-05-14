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
#include "Alarm.h"
#include "util/delay.h"


int main(void)
{
    /* Replace with your application code */
	
	ds1307_init();
	ds1307_setdate(12, 12, 31, 3, 23, 54, 55);
	//setAlarm(2356);
	//setAlarm(2355);
	int mode = 0;
    while (1) 
    {
		checkAlarm();
		if (isPress(PIND0)){
			mode++;
			_delay_ms(500);
		}
		if (mode == 3){
			ringAlarm();
		}	
	}
}

