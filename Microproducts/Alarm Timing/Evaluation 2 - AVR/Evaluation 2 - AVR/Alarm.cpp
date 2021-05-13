/* 
* Alarm.cpp
*
* Created: 5/13/2021 8:39:09 PM
* Author: Dakshina Tharidndu
*/


#include "Alarm.h"
#include "util/delay.h"
#include <avr/io.h>

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
void ringAlarm(){
	DDRB = 1<<PORTB0;
	PORTB = 1<<PORTB0;
	_delay_ms(6000);
	PORTB = 0<<PORTB0;
}
void setAlarm(int alarm_time){
	alarmArray[numberOfAlarms] = alarm_time;
	numberOfAlarms++;
}
void checkAlarm(int h , int m){
	if (numberOfAlarms != 0){
		for (int i = 0; i <= numberOfAlarms;i++){
			if (alarmArray[i]/100 == h && alarmArray[i]%100 == m){
				ringAlarm();
				numberOfAlarms--;
			}
		}
		
	}
}