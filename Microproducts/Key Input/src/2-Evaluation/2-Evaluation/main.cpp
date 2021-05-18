/*
 * 2-Evaluation.cpp
 *
 * Created: 5/12/2021 2:30:58 PM
 * Author : Asus
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int key1,key2,i,rowloc,colloc;
char keys[4][3] = {{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}} ;
char keypad();
char key;

int main(void)
{
	while (1)
	{
		DDRD = 0b011111111;   /* Make all pins of PORTD as output pins */
		key = keypad();
		if (key == '1') { PORTD = 0b00100010; }
		if (key == '2') { PORTD = 0b00011111; }
		if (key == '3') { PORTD = 0b00110111; }
		if (key == '4') { PORTD = 0b01100110; }
		if (key == '5') { PORTD = 0b01110101; }
		if (key == '6') { PORTD = 0b01111101; }
		if (key == '7') { PORTD = 0b00100011; }
		if (key == '8') { PORTD = 0b01111111; }
		if (key == '9') { PORTD = 0b01100111; }
		if (key == '*' || key =='#'){
			PORTD = 0b00000000;
			for(i=0;i<7;i++){
			PORTD |= (1<<i);
			_delay_ms(100);}
		}
		if (key == '0') { PORTD = 0b01111011; }
	}
}

char keypad(){
	while(1){
		DDRB = 0b01111111;
		PORTB = 0b01111000;
	
		key1 = PINB & 0b00000111;     /*get the pressed key*/
		_delay_us(5);
	
		DDRB = 0b01111111;
		PORTB = 0b00000111;
	
		key2 = PINB & 0b01111000;
		_delay_us(5);
	
		if (key1 == 0b00000001) { colloc = 2; break; }
		if (key1 == 0b00000010) { colloc = 1; break; }
		if (key1 == 0b00000100) { colloc = 0; break; }
	}
	
	if (key2 == 0b00001000)  return(keys[0][colloc]); 
	else if (key2 == 0b00010000)  return(keys[1][colloc]); 
	else if (key2 == 0b00100000)  return(keys[2][colloc]); 
	else if (key2 == 0b01000000)  return(keys[3][colloc]);
	else return(0);
		
}

