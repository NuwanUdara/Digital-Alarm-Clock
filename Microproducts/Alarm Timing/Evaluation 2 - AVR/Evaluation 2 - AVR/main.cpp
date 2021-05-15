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
#define button_delay 500

int mode = 0;
int data = 0;
int state = 3;
int alarmTime = 0;
void getAlarmTime(){
	if (isPress(PORTD1)){
		data++;
		_delay_ms(button_delay);
	}
	if (isPress(PORTD2)){
		alarmTime += data*powerOf(10,state);
		state--;
		data=0;
	}
	if (state == -1){
		setAlarm(alarmTime);
		state = 3;
		mode = 0;
	}
}
int main(void)
{
    /* Replace with your application code */
	
	ds1307_init();
	ds1307_setdate(12, 12, 31, 3, 23, 54, 55);
	//setAlarm(2356);
	//setAlarm(2355);
    while (1) 
    {
		checkAlarm();
		if (isPress(PIND0)){
			mode++;
			_delay_ms(button_delay);
		}
		if (mode == 1){
			getAlarmTime();
		}	
	}
}

