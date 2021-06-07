
#include <avr/io.h>
#include <util/delay.h>

#define data_direction DDRB
#define port_state PORTB
#define key_pin PINB

int key1,key2,colloc;


char getkey(char keymap[][3]){
	
	while(1){
		data_direction = 0b01111111;      /*DDRB 1 output, 0 input*/
		port_state = 0b01111000;          /*PORTB 1 high, 0 low*/
		
		key1 = key_pin & 0b00000111;     /* read status of column */
		_delay_us(5);                    /*key debounce time */
		
		data_direction = 0b01111111;
		port_state = 0b00000111;
		
		key2 = key_pin & 0b01111000;      /* read status of row */
		_delay_us(5);                     /*key debounce time */
		
		if (key1 == 0b00000001) { colloc = 2; break; }   /*find the column which pressed*/
		if (key1 == 0b00000010) { colloc = 1; break; }
		if (key1 == 0b00000100) { colloc = 0; break; }
	}
	
	if (key2 == 0b00001000)  return(keymap[0][colloc]);
	else if (key2 == 0b00010000)  return(keymap[1][colloc]);  /*return the key*/
	else if (key2 == 0b00100000)  return(keymap[2][colloc]);
	else if (key2 == 0b01000000)  return(keymap[3][colloc]);
	else return(0);
	
}
