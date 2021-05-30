
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
		lcd_puts("  MENU1");
		lcd_gotoxy(0,1);
		lcd_puts(">>MENU2");
			
	}
}
void second(){
	if(PINC & (1<<0)){
		lcd_clrscr();
		lcd_home();
		lcd_puts("  MENU2");
		lcd_gotoxy(0,1);
		lcd_puts(">>MENU3");
		
	}
}
int main(void)
{
	DDRC = DDRC & ~(1<<0);
	lcd_init(LCD_DISP_ON_CURSOR);
	/* Replace with your application code */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */
	lcd_puts(">>MENU1");
	lcd_gotoxy(0,1);
	lcd_puts("  MENU2");

	
	
	
	while (1)
	{	
		first();
		_delay_ms(50);
		second();
		_delay_ms(50);
		
		
	
	}
}

