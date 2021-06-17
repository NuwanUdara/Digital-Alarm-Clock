#include "Keypad.h"
#include <avr/io.h>
#include <util/delay.h>
#define keyPort PINC
#define keyPin PIND
char keys[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
uint8_t row[4] = {PORTD4,PORTD5,PORTD6,PORTD7};
uint8_t colomn[3] = {PIND0,PIND1,PIND2};
// default constructor
Keypad::Keypad()
{
} //Keypad

// default destructor
Keypad::~Keypad()
{
} //~Keypad


char btnPress(){
	DDRD = 0xF0;
	for (int i=0;i<4;i++){
		PORTD = 1<<row[i];
		//_delay_ms(500);
		for (int j = 0;j<3;j++){
			if ((PIND & 1<<colomn[j]) == (1<<colomn[j])){
				//_delay_ms(100);
				return keys[i][j];
			}
		}
	}
	return '&';
}