/* 
* Alarm.h
*
* Created: 5/13/2021 8:39:09 PM
* Author: Dakshina Tharidndu
*/


#ifndef __ALARM_H__
#define __ALARM_H__
#include <avr/io.h>
class Alarm
{
//variables
public:
protected:
private:

//functions
public:
	Alarm();
	~Alarm();
	
protected:
private:
	Alarm( const Alarm &c );
	Alarm& operator=( const Alarm &c );

}; //Alarm
extern bool isPress(uint8_t prt);
extern int powerOf(int base, int power);
//extern void getAlarmTime();
extern void ringAlarm(int tone);
extern void setAlarm(int alarm_time);
extern void checkAlarm();
extern void updateAlarmArray(int removeAlarm);
extern void setClockTime(int clockTime[6]);
extern int getDay(int y, int m, int d);
extern void displayTime();
extern void displayZero(uint8_t digit);
extern void setTone(int t);
extern void timer(char key,int state);
extern void timerCountDown();
#endif //__ALARM_H__
