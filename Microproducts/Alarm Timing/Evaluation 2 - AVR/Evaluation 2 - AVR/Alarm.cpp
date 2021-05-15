/* 
* Alarm.cpp
*
* Created: 5/13/2021 8:39:09 PM
* Author: Dakshina Tharidndu
*/


#include "Alarm.h"
#include "util/delay.h"
#include <avr/io.h>
#include "ds1307.h"
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

// default constructor
Alarm::Alarm()
{
} //Alarm

// default destructor
Alarm::~Alarm()
{
} //~Alarm
int numberOfAlarms = 0;
int alarmArray[10];
uint8_t year = 0;
uint8_t month = 0;
uint8_t day = 0;
uint8_t dayofweek = 0;
uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
int powerOf(int base, int power){
	int result = 1;
	while(power!=0){
		result*=base;
		power--;
	}
	return result;
	
}
bool isPress(uint8_t prt){
	if (PIND == 1<< prt){
		return true;
	}
	else{
		return false;
	}
}
void ringAlarm(){
	DDRB |= 1<<PORTB0;
	PORTB |= 1<<PORTB0;
	_delay_ms(6000);
	PORTB = 0;
}
void setAlarm(int alarm_time){
	alarmArray[numberOfAlarms] = alarm_time;
	numberOfAlarms++;
}
void updateAlarmArray(int removeAlarm){
	for (int i=0;i<numberOfAlarms;i++){
		if (i<removeAlarm){
			alarmArray[i] = alarmArray[i];
		}
		else{
			alarmArray[i] = alarmArray[i+1];
		}
	}
}
void checkAlarm(){
	if (numberOfAlarms != 0){
		ds1307_getdate(&year, &month, &day, &dayofweek, &hour, &minute, &second);
		for (int i = 0; i <= numberOfAlarms;i++){
			if (alarmArray[i]/100 == hour && alarmArray[i]%100 == minute){
				ringAlarm();
				updateAlarmArray(i);
				numberOfAlarms--;
			}
		}
		
	}
}
void setClockTime(unsigned long long clockTime){
	int y = clockTime/100000000000;
	int m = (clockTime/1000000000)%100;
	int d = (clockTime/10000000)%100;
	int D = (clockTime/1000000)%10;
	int h = (clockTime/10000)%100;
	int M = (clockTime/100)%100;
	int s = clockTime%100;
	ds1307_setdate(y, m, d, D, h, M, s);
}