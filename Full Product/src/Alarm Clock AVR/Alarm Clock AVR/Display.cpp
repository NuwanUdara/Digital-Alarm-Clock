
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>
#define BUTTON_DELAY 500
#include "Display.h"
#include "Keypad.h"
#include "stdlib.h"
#include "Alarm.h"
#define LCD_Dir  DDRD			/* Define LCD data port direction */
#define LCD_Port PORTD			/* Define LCD data port */
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
int blink_var=0;
void LCD_Blink(char ch[10]){
	if (blink_var==0){
		LCD_String(ch);
		blink_var=1;
		_delay_ms(100);
	}
	else{
		LCD_String(" ");
		blink_var=0;
		_delay_ms(100);
	}
}
void displayTyping(int val,int pos){
	char val0S[2];char val1S[2];
	itoa(val/10,val0S,10);itoa(val%10,val1S,10);
	if (pos==0){
		LCD_Blink(val0S);
		LCD_String(val1S);
	}
	else if (pos==1){
		LCD_String(val0S);
		LCD_Blink(val1S);
	}
	else{
		LCD_String(val0S);LCD_String(val1S);
	}
}
int clkTime = 0;
int num = 0;
signed int p = 3;
void LCD_SetAlarm(char key,int state){
	if (p!=-1){
		LCD_Home(0);
		LCD_String("     ");
		displayTyping(clkTime/100,3-p);
		LCD_String(":");
		displayTyping(clkTime%100,1-p);
	}
	//LCD_String("0000");
	if ((int(key)>47) & (int(key)<58) & (state ==2) & (p!=-1)){
		clkTime += (int(key)-48)*powerOf(10,p);
		p--;
		_delay_ms(BUTTON_DELAY);
		if (p==-1){
			LCD_Home(0);
			LCD_String("     ");
			displayTyping(clkTime/100,3);LCD_String(":");displayTyping(clkTime%100,3);
			_delay_ms(1000);
			LCD_Home(0);
			LCD_String("SELECT THE TONE");
			_delay_ms(2000);
			LCD_Clear();
		}
	}
	if (p==-1){
		LCD_Tone(key,state);
	}
	if (state==3){
		setAlarm(clkTime);
		LCD_Home(0);
		LCD_String("ALARM IS SET TO");
		LCD_Home(1);
		displayTyping(clkTime/100,3);LCD_String(":");displayTyping(clkTime%100,3);
		clkTime=0;num=0;p=3;
		_delay_ms(2000);
		LCD_Clear();
	}
}
int clockTime[6];
int ClockState = 0;
int temp = 0;
int data = 0;
char dataS[10];
void LCD_SetDate(int key, int state){
	LCD_Home(0);
	LCD_String("   20");
	for (int i=0;i<6;i++){
		if (i==3){
			LCD_Home(1);
			LCD_String("    ");
		}
		if ((i!=3) & (i!=0)){
			LCD_String(":");
		}
		if (i==ClockState){
			displayTyping(clockTime[i],temp);
		}
		else{
			displayTyping(clockTime[i],3);
		}
	}
	if ((int(key)>47) & (int(key)<58) & (state ==2)){
		data+=(int(key)-48);
		_delay_ms(BUTTON_DELAY);
		if (temp == 0){
			data*=10;
			temp = 1;
			clockTime[ClockState] = data;
		}
		else{
			clockTime[ClockState] = data;
			ClockState++;
			data=0;
			temp = 0;
		}
	}
	if ((ClockState == 6) & (state==3)){
		setClockTime(clockTime);
		ClockState = 0;
		LCD_Home(0);LCD_Clear();
		LCD_String("      DONE!");
		_delay_ms(2000);
		LCD_Clear();
	}
}
char tone_List[5][10] = {"DOOM     ","STAR WARS","GOT      ","PANTHER  ","GODFATHER"};
int tone_Var = 0;
void LCD_Tone(char key,int state){
	LCD_Home(0);
	if ((key=='8') & (state==2)){
		tone_Var++;
		//LCD_Clear();
		_delay_ms(BUTTON_DELAY);
	}
	if ((key=='2') & (state ==2)){
		tone_Var--;
		//LCD_Clear();
		_delay_ms(BUTTON_DELAY);
	}
	if (tone_Var>4){
		tone_Var=0;
	}
	if (tone_Var<0){
		tone_Var=4;
	}
	if (state==2){
		LCD_Home(0);LCD_String(">>");
		LCD_String(tone_List[tone_Var%5]);
		// 	LCD_Home(1);
		// 	LCD_String(menu_List[(menu_Var+1)%3]);
	}
	 if (state==3){
		 setTone(tone_Var);
	 }

}
char menu_List[4][11] = {"SET ALARM ","SET TIME  ","SEE ALARMS","TIMER     "};
int menu_Var = 0;
void LCD_Menu(char key,int state){
	LCD_Home(0);
	if ((key=='8') & (state==1)){
		menu_Var++;
		//LCD_Clear();
		_delay_ms(BUTTON_DELAY);
	}
	if ((key=='2') & (state ==1)){
		menu_Var--;
		//LCD_Clear();
		_delay_ms(BUTTON_DELAY);
	}
	if (menu_Var>3){
		menu_Var=0;
	}
	if (menu_Var<0){
		menu_Var=3;
	}
	if (state==1){
		LCD_Home(0);LCD_String(">>");
		LCD_String(menu_List[menu_Var%4]);
		resetVariables();
	// 	LCD_Home(1);
	// 	LCD_String(menu_List[(menu_Var+1)%3]);
	}
	if ((state >1) & (menu_Var==0)){
		LCD_SetAlarm(key,state);
	}
	if ((state >1) & (menu_Var==1)){
		LCD_SetDate(key,state);
	}
	if ((state >1) & (menu_Var==2)){
		showAlarms(key,state);
	}
	if ((state >1) & (menu_Var==3)){
		timer(key,state);
	}
}
void resetVariables(){
	resetAlarmVariables();
	tone_Var=0;
	clockTime[0]=0;clockTime[1]=0;clockTime[2]=0;clockTime[3]=0;clockTime[4]=0;clockTime[5]=0;
	ClockState = 0;
	temp = 0;
	data = 0;
	clkTime = 0;
	num = 0;
	p = 3;
}
