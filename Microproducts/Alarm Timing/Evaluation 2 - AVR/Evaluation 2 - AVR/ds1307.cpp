#ifndef DS1307_H
#define DS1307_H
#include "ds1307.h"
#include <avr/io.h>

uint8_t ds1307_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}
uint8_t ds1307_bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}
#endif