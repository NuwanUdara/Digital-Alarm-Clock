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
void ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t dayofweek, uint8_t hour, uint8_t minute, uint8_t second) {
	

	i2c_start_wait(DS1307_ADDRESS | I2C_WRITE);
	i2c_write(0x00);
	i2c_write(ds1307_dec2bcd(second));
	i2c_write(ds1307_dec2bcd(minute));
	i2c_write(ds1307_dec2bcd(hour));
	i2c_write(ds1307_dec2bcd(dayofweek));
	i2c_write(ds1307_dec2bcd(day));
	i2c_write(ds1307_dec2bcd(month));
	i2c_write(ds1307_dec2bcd(year));
	i2c_write(0x00);
	i2c_stop();
}
#endif