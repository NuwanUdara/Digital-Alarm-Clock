
#include "Keypad.h"
#include <avr/io.h>
#include <util/delay.h>
#define keyPort PINC
#define keyPin PIND
char keys[4][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
uint8_t row[4] = {PORTC0,PORTC1,PORTC2,PORTC3};
uint8_t colomn[3] = {PIND4,PIND5,PIND6};
// default constructor
Keypad::Keypad()
{
} //Keypad

// default destructor
Keypad::~Keypad()
{
} //~Keypad


char btnPress(){
	DDRC = 0x0F;
	for (int i=0;i<4;i++){
		PORTC = 1<<row[i];
		for (int j = 0;j<3;j++){
			if (PIND==(1<<colomn[j])){
				//_delay_ms(100);
				return keys[i][j];
			}
		}
	}
	return '&';
}