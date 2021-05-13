/* 
* Alarm.cpp
*
* Created: 5/13/2021 8:39:09 PM
* Author: Dakshina Tharidndu
*/


#include "Alarm.h"
#include "util/delay.h"
#include <avr/io.h>

// default constructor
Alarm::Alarm()
{
} //Alarm

// default destructor
Alarm::~Alarm()
{
} //~Alarm
void ringAlarm(){
	DDRB = 1<<PORTB0;
	PORTB = 1<<PORTB0;
	_delay_ms(4000);
	PORTB = 0<<PORTB0;
}