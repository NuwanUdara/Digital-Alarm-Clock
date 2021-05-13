/* 
* Alarm.h
*
* Created: 5/13/2021 8:39:09 PM
* Author: Dakshina Tharidndu
*/


#ifndef __ALARM_H__
#define __ALARM_H__


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
extern void ringAlarm();
extern void setAlarm(int alarm_time);
extern void checkAlarm(int h , int m);

#endif //__ALARM_H__
