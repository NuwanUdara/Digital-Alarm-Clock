#include <avr/io.h>			/* Include AVR std. library file */
#include <avr/interrupt.h>
#include "Display.h"
#include "ds1307.h"
#include "Alarm.h"
#include "Keypad.h"
#include "util/delay.h"
#include "Buzzer.h"
#define BUTTON_DELAY 600

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
int main()
{
	init_buzzer();		// Initialize pins used for buzzer and Interrupt button
	LCD_Init();			/* Initialization of LCD*/
	LCD_String("   WELCOME!!!");
	_delay_ms(1000);
	LCD_Clear();
	ds1307_init();
	int clocktime[6] = {21,05,4,12,8,35};
	setClockTime(clocktime);
	setAlarm(1222);setAlarm(1233);setAlarm(1244);setAlarm(1255);
	int menu = 0;
	char key;
	while(1){
		checkAlarm();
		key = btnPress();
		if (menu==0){
			displayTime();
		}
		if (key=='*'){
			_delay_ms(BUTTON_DELAY);
			menu ++;
			LCD_Clear();
		}
		if (menu>0){
			LCD_Menu(key,menu);
		}
		if (menu==3 | menu==-1){
			menu = 0;
		}
		if (key=='#'){
			_delay_ms(BUTTON_DELAY);
			menu --;
			LCD_Clear();
		}
	}
}
