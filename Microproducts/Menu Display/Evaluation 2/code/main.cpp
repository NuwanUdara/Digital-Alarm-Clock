
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include "lcd/lcd.h"
#include <util/delay.h>
int menu =0;
int k = 1;


int main(void)
{
	DDRC = ~(1<<0);
	DDRC = ~(1<<1);
	DDRC = ~(1<<2);
	DDRC = ~(1<<3);
	lcd_init(LCD_DISP_ON_CURSOR);
	
	lcd_clrscr();             /* clear screen of lcd */
	lcd_home();               /* bring cursor to 0,0 */

	while (1)
	{	
		if ((PINC & (1<<0))){
			menu++;
			update_menu();
			_delay_ms(50);
			(PINC & (1<<0))==0;
		
		}
		
		if ((PINC & (1<<1))){
			menu--;
			update_menu();
			_delay_ms(50);
			(PINC & (1<<1))==0;
			
		}
		if ((PINC & (1<<2))){
			execute();
			
			_delay_ms(50);
			
		}	
	}
}
void update_menu(){
	switch(menu){		
		case 1:
			lcd_clrscr();
			lcd_home();
			lcd_puts(">>TIME");
			lcd_gotoxy(0,1);
			lcd_puts("  DATE");		
			break;
		case 2:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  TIME");
			lcd_gotoxy(0,1);
			lcd_puts(">>DATE");			
			break;
		case 3:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  DATE");
			lcd_gotoxy(0,1);
			lcd_puts(">>TONE");
			break;
		case 4:
			lcd_clrscr();
			lcd_home();
			lcd_puts("  TONE");
			lcd_gotoxy(0,1);
			lcd_puts(">>COLOR");	
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
	lcd_puts("TIME_showing");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);
	if ((PINC & (1<<3))){
		update_menu();	
	}

	
}
void action2(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("DATE_showing");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(100);
	if ((PINC & (1<<3))){
		update_menu();
	}

}
void action3(){

	while(1){
		if ((PINC & (1<<0))){
			k++;
		}
		if ((PINC & (1<<1))){
			k--;
		}
		if ((PINC & (1<<3))){
			break;	
		}
		

		switch(k){
			case 1:
				lcd_clrscr();
				lcd_home();
				lcd_puts(">>PIRATES_OF_CARIBEAN");
				lcd_gotoxy(0,1);
				lcd_puts("  GAME_OF_THRONES");
				_delay_ms(50);
				break;
			case 2:
				lcd_clrscr();
				lcd_home();
				lcd_puts("  PIRATES_OF_CARIBEAN");
				lcd_gotoxy(0,1);
				lcd_puts(">>GAME_OF_THRONES");
				_delay_ms(50);
				break;
			case 3:
				lcd_clrscr();
				lcd_home();
				lcd_puts("  GAME_OF_THRONES");
				lcd_gotoxy(0,1);
				lcd_puts(">>HOBBIT");
				_delay_ms(50);
				break;
			case 4:
				lcd_clrscr();
				lcd_home();
				lcd_puts("  HOBBIT");
				lcd_gotoxy(0,1);
				lcd_puts(">>BEUATY_AND_BEAST");
				_delay_ms(50);
				break;
		}
	}
	update_menu();
}
void action4(){
	lcd_clrscr();
	lcd_home();
	lcd_puts("4th_submenu");
	lcd_gotoxy(0,1);
	lcd_puts("-----------");
	_delay_ms(50);

}
	