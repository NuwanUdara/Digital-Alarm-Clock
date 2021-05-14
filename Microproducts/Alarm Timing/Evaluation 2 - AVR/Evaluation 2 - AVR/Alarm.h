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
extern void getAlarmTime();
extern void ringAlarm();
extern void setAlarm(int alarm_time);
extern void checkAlarm();
extern void updateAlarmArray(int removeAlarm);

#endif //__ALARM_H__
