/*
 * GccApplication4.c
 *
 * Created: 5/18/2021 7:23:43 PM
 * Author : lenovo
 */ 
#include <avr/io.h>
#include "lcd/lcd.h"

int main(void)
{
	
	lcd_init(LCD_DISP_ON_CURSOR);
	lcd_clrscr();             
	lcd_home();               
	lcd_puts("hello");        
	lcd_gotoxy(0,1);          
	lcd_puts("I'm tharindu");  
	while (1)
	{
	}
}

