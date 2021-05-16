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
	if (isPress(PIND1)){
		data++;
		_delay_ms(button_delay);
	}
	if (isPress(PIND2)){
		alarmTime += data*powerOf(10,state);
		state--;
		data=0;
		_delay_ms(button_delay);
	}
	if (state == -1){
		setAlarm(alarmTime);
		state = 3;
		mode = 0;
		_delay_ms(button_delay);
	}
}
int main(void)

{	setClockTime(1212123115437);
	ds1307_init();
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

