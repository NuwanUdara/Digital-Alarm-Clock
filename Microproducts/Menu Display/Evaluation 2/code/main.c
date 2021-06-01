
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "lcd/lcd.h"
#include <util/delay.h>
int menu =0;


int main(void)
{
	DDRC = ~(1<<0);
	DDRC = ~(1<<1);
	lcd_init(LCD_DISP_ON_CURSOR);
	/* Replace with your application code */
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */

	while (1)
	{	
		if ((PINC & (1<<0))){
			menu++;
			update_menu();
			_delay_ms(100);
			(PINC & (1<<0))==0;
		
		}
		
		if ((PINC & (1<<1))){
			menu--;
			update_menu();
			_delay_ms(100);
			(PINC & (1<<1))==0;
			
		}
		if ((PINC & (1<<2))){
			execute();
			
			_delay_ms(100);
			
		}	
	}
}
void update_menu(){
	switch(menu){		
		case 1:
			lcd_clrscr();
			lcd_home();
			lcd_puts(">>MENU1");
			lcd_gotoxy(0,1);
			lcd_puts("  MENU2");		
			break;
		case 2:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  MENU1");
			lcd_gotoxy(0,1);
			lcd_puts(">>MENU2");			
			break;
		case 3:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  MENU2");
			lcd_gotoxy(0,1);
			lcd_puts(">>MENU3");
			break;
		case 4:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  MENU3");
			lcd_gotoxy(0,1);
			lcd_puts(">>MENU4");	
			break;
		
	}
}
void execute(){
	switch(menu){
		case 1:
			action1();
			break;
		case 2:
			action2();
			break;
		case 3:
			action3();
			break;
		case 4:
			action4();
			break;	
	}
}
void action1(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("1st_submenu");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);
	
}
void action2(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("2nd_submenu");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);

}
void action3(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("3rd_submenu");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);

}
void action4(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("4th_submenu");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);

}
	