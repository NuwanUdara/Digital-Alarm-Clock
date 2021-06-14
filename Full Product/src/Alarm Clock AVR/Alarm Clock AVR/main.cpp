#include <avr/io.h>			/* Include AVR std. library file */
#include "Display.h"
#include "ds1307.h"
#include "Alarm.h"
#include "Keypad.h"
#include "util/delay.h"
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
int main()
{
	LCD_Init();			/* Initialization of LCD*/
	LCD_String("   WELCOME!!!");
	_delay_ms(1000);
	LCD_Clear();
	ds1307_init();
	int clocktime[6] = {21,05,4,12,8,35};
	setClockTime(clocktime);
	setAlarm(1209);
	int menu = 0;
	char key;
	while(1){
		checkAlarm();
		key = btnPress();
		if (menu==0){
			displayTime();
		}
		if (key=='*'){
			_delay_ms(400);
			menu ++;
			LCD_Clear();
		}
		if (menu>0){
			LCD_Menu(key,menu);
		}
		if (menu==3){
			menu = 0;
		}
		if (key=='#'){
			_delay_ms(100);
			menu --;
			LCD_Clear();
		}
	}
}
