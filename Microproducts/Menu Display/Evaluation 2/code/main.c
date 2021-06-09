
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>        /*add OI header file*/
#include "lcd/lcd.h"       /*add LCD header file*/
#include <util/delay.h>    /*add Time delay header file*/
int menu =0;
int sub_menu = 1;


int main(void)
{   /* I use C port to give inputs*/
	DDRC = ~(1<<0);        /*set C-0 port as input pin  using data direction register of portC --1111110--*/  
	DDRC = ~(1<<1);		   /*set C-1 port as input pin  using data direction register of portC --1111101--*/ 
	DDRC = ~(1<<2);		   /*set C-2 port as input pin*/ 
	DDRC = ~(1<<3);		   /*set C-3 port as input pin*/ 
	lcd_init(LCD_DISP_ON_CURSOR);     /*LCD initialization and display on*/

	
	lcd_clrscr();             /* clear screen of LCD */
	lcd_home();               /* bring cursor to 0,0 */
	lcd_puts(">>MENU DISPLAY<<");         /*display LCD*/

	while (1)
	{	
		if ((PINC & (1<<0))){      /*check voltage input from DOWN button    --0000001 & 0000001--*/ 
			menu++;                /*increment the menu value*/
			update_menu();         /*called update_menu() function*/
			_delay_ms(50);         /*set delay*/
			(PINC & (1<<0))==0;
		
		}
		
		if ((PINC & (1<<1))){       /*check voltage input from UP button      --0000010 & 0000010--*/ 
			menu--;                 /*decrement the sub_menu value*/
			update_menu();
			_delay_ms(50);
			(PINC & (1<<1))==0;
			
		}
		if ((PINC & (1<<2))){        /*check voltage input from ENTER button*/ 
			execute();               /*called execute() function*/
			
			_delay_ms(50);
			
		}	
	}
}
void update_menu(){           /*check menu value and LCD display*/
	switch(menu){		    
		case 1:               /*if menu = 1*/
			lcd_clrscr();
			lcd_home();
			lcd_puts(">>TIME");
			lcd_gotoxy(0,1);             /*go to second raw of LCD panel*/
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
	
	}
}
void execute(){         /*check menu value and call the relative functions*/
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
	}
}
void action1(){                /*sub menu of time*/
	while(1){
		lcd_clrscr();
		lcd_home();
		lcd_puts("TIME_showing");
		lcd_gotoxy(0,1);
		lcd_puts(">>3.00 P.M.");         /*example for time showing*/
		_delay_ms(50);
		if ((PINC & (1<<3))){            /*check voltage input from BACK button*/ 
			break;	
		}
	}
	update_menu();          /*go to the main menu_s*/
	

	
}
void action2(){                        /*sub menu of date*/
	while(1){
		lcd_clrscr();
		lcd_home();
		lcd_puts("DATE_showing");
		lcd_gotoxy(0,1);
		lcd_puts("25th_Of_june2021");                /*example for date showing*/
		_delay_ms(50);
		if ((PINC & (1<<3))){
			break;
		}
	}
	update_menu();                      /*go to the main menu_s*/

}
void action3(){                           /*sub menu of tone*/

	while(1){    /*same here as main function*/
		if ((PINC & (1<<0))){             
			sub_menu++;                   /*increment the sub_menu value*/
		}
		if ((PINC & (1<<1))){
			sub_menu--;                   /*decrement the sub_menu value*/
		}
		if ((PINC & (1<<3))){             /*if press BACK button break the loop*/
			break;	
		}
		

		switch(sub_menu){                 /*check sub_menu value and display*/
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
			 case 5:
				 lcd_clrscr();
				 lcd_home();
				 lcd_puts("  BEUATY_AND_BEAST");
				 lcd_gotoxy(0,1);
				 lcd_puts(">>FAST AND FURIOUS");
				 _delay_ms(50);
				 break;
		}
	}
	update_menu();                /*go to the main menu_s*/
}

	