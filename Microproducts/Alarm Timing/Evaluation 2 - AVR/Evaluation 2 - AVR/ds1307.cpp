#ifndef DS1307_H
#define DS1307_H
#include "ds1307.h"
#include <avr/io.h>
#include "i2cmaster.h"
#define DS1307_ADDRESS 0xD0

uint8_t ds1307_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}
uint8_t ds1307_bcd2dec(uint8_t val) {
	return val - 6 * (val >> 4);
}
#endif