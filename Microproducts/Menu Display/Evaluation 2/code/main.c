
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "lcd/lcd.h"
#include <util/delay.h>
void first(){
	if(PINC & (1<<0)){
		lcd_clrscr();
		lcd_home();
		lcd_puts(">>MENU1");
		lcd_gotoxy(0,1);
		lcd_puts("  MENU2");
		_delay_ms(100);
		if(PINC & (1<<1)){
			lcd_clrscr();
			lcd_home();
			lcd_puts(">>SUB MENU 01");
			lcd_gotoxy(0,1);
			lcd_puts("  SUB MENU 02");
			_delay_ms(100);
			DDRC = ~DDRC & (1<<0);
		}
	}
}
void second(){
	if(PINC & (1<<0)){
		lcd_clrscr();
		lcd_home();
		lcd_puts("  MENU1");
		lcd_gotoxy(0,1);
		lcd_puts(">>MENU2");
		_delay_ms(100);
		DDRC = ~DDRC & (1<<0);
			
	}
}
void third(){
	if(PINC & (1<<0)){
		lcd_clrscr();
		lcd_home();
		lcd_puts("  MENU2");
		lcd_gotoxy(0,1);
		lcd_puts(">>MENU3");
		_delay_ms(100);
		DDRC = ~DDRC & (1<<0);
		
	}
}
int main(void)
{
	DDRC = DDRC & ~(1<<0);
	DDRC = DDRC & ~(1<<1);
	lcd_init(LCD_DISP_ON_CURSOR);
	/* Replace with your application code */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */
	lcd_puts(">>MENU1");
	lcd_gotoxy(0,1);
	lcd_puts("  MENU2");

	
	
	
	while (1)
	{	
		second();
		third();
		first();
		
		
		
	
	}
}

