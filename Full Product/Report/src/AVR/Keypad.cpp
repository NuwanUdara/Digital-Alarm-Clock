
#include "Keypad.h"
#include <avr/io.h>
#include <util/delay.h>
#define keyDir DDRC
#define keyPort PORTC
#define keyPin PINB
char keys[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
uint8_t row[4] = {PORTC0,PORTC1,PORTC2,PORTC3};
uint8_t colomn[3] = {PINB0,PINB1,PINB2};
// default constructor
Keypad::Keypad()
{
} //Keypad

// default destructor
Keypad::~Keypad()
{
} //~Keypad


char btnPress(){
	keyDir = 0x0F;
	for (int i=0;i<4;i++){
		keyPort = 1<<row[i];
		for (int j = 0;j<3;j++){
			if (keyPin==(1<<colomn[j])){
				//_delay_ms(100);
				return keys[i][j];
			}
		}
	}
	return '&';
}