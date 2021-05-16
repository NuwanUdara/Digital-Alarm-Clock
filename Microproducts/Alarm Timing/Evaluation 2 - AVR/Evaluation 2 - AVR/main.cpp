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
int AlarmState = 3;
int ClockState = 0;
int temp = 0;
int alarmTime = 0;
int clockTime[6];
void getAlarmTime(){
	if (isPress(PIND1)){
		data++;
		_delay_ms(button_delay);
	}
	if (isPress(PIND2)){
		alarmTime += data*powerOf(10,AlarmState);
		AlarmState--;
		data=0;
		_delay_ms(button_delay);
	}
	if (AlarmState == -1){
		setAlarm(alarmTime);
		AlarmState = 3;
		mode = 0;
		_delay_ms(button_delay);
	}
}
void getClockTime(){
	if (isPress(PIND1)){
		data++;
		_delay_ms(button_delay);
	}
	if (isPress(PIND2)){
		if (temp == 0){
			data*=10;
			temp = 1;
		}
		else{
			clockTime[ClockState] = data;
			ClockState++;
			data=0;
			temp = 0;
		}
		_delay_ms(button_delay);
	}
	if (ClockState == 6){
		setClockTime(clockTime);
		ClockState = 0;
		mode = 0;
		_delay_ms(button_delay);
	}
}
int main(void)
{	
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
		if (mode == 2){
			getClockTime();
		}	
	}
}

