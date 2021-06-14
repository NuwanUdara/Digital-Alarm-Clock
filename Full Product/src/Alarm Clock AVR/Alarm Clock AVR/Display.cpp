
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>

#include "Display.h"
#include "Keypad.h"
#include "stdlib.h"
#include "Alarm.h"
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pin */
// default constructor
Display::Display()
{
} //Display

// default destructor
Display::~Display()
{
} //~Display
void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);		/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Dir = 0xFF;			/* Make LCD port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_Command(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);              /* Display on cursor off*/
	LCD_Command(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);              /* Clear display screen*/
	_delay_ms(2);
}

//char temp1='/';
void LCD_String (char *str)		/* Send string to LCD function */
{
		int i;
		for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
		{
			LCD_Char (str[i]);
		}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}
void LCD_Home(int r){
	if(r==0){
		LCD_Command (0x80);
	}
	else{
		LCD_Command (0xC0);
	}
}

int clkTime = 0;
int num = 0;
signed int p = 3;
char clkTimeS[10];
void LCD_SetAlarm(char key,int state){
	LCD_Home(0);
	if (clkTime==0){
		LCD_String("0000");
	}
	//LCD_String("0000");
	if (int(key)>47 & int(key)<58 & state ==2 & p!=-1){
		LCD_Home(0);
		clkTime += (int(key)-48)*powerOf(10,p);
		itoa(clkTime,clkTimeS,10);
		LCD_String(clkTimeS);
		p--;
		_delay_ms(800);
	}
	if (state==3){
		setAlarm(clkTime);
		LCD_Home(0);
		LCD_String("ALARM IS SET TO");
		LCD_Home(1);
		LCD_String(clkTimeS);
		clkTime=0;num=0;p=3;
		_delay_ms(2000);
		LCD_Clear();
	}


}

char menu_List[3][10] = {"SET ALARM","SET TIME ","SET TONE "};
int menu_Var = 0;
void LCD_Menu(char key,int state){
	LCD_Home(0);
	if (key=='8' & state==1){
		menu_Var++;
		//LCD_Clear();
		_delay_ms(800);
	}
	if (key=='2' & state ==1){
		menu_Var--;
		//LCD_Clear();
		_delay_ms(800);
	}
	if (menu_Var>2){
		menu_Var=0;
	}
	if (menu_Var<0){
		menu_Var=2;
	}
	if (state==1){
		LCD_Home(0);LCD_String(">>");
		LCD_String(menu_List[menu_Var%3]);
	// 	LCD_Home(1);
	// 	LCD_String(menu_List[(menu_Var+1)%3]);
	}
	if ((state >1) & (menu_Var==0)){
		LCD_SetAlarm(key,state);
	}
}
