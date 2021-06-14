/* 
* Keypad.h
*
* Created: 6/13/2021 11:40:03 AM
* Author: Dakshina Tharidndu
*/


#ifndef __KEYPAD_H__
#define __KEYPAD_H__


class Keypad
{
//variables
public:
protected:
private:

//functions
public:
	Keypad();
	~Keypad();
protected:
private:
	Keypad( const Keypad &c );
	Keypad& operator=( const Keypad &c );

}; //Keypad
extern char btnPress();
#endif //__KEYPAD_H__
