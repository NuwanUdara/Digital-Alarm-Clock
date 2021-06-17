/* 
* Display.h
*
* Created: 6/11/2021 6:58:37 PM
* Author: Dakshina Tharidndu
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__


class Display
{
//variables
public:
protected:
private:

//functions
public:
	Display();
	~Display();
protected:
private:
	Display( const Display &c );
	Display& operator=( const Display &c );

}; //Display
extern void LCD_Command( unsigned char cmnd );
extern void LCD_Char( unsigned char data );
extern void LCD_Init (void);
extern void LCD_String (char *str);
extern void LCD_String_xy (char row, char pos, char *str);
extern void LCD_Clear();
extern void LCD_Home(int r);
extern void LCD_Menu(char key,int state);
extern void LCD_SetAlarm(char key,int state);
extern void LCD_SetDate(int key, int state);
extern void LCD_Tone(char key,int state);
#endif //__DISPLAY_H__
