#include <avr/io.h>
extern uint8_t ds1307_dec2bcd(uint8_t val);
extern uint8_t ds1307_bcd2dec(uint8_t val);
extern void ds1307_init();
extern void ds1307_setdate(uint8_t year, uint8_t month, uint8_t day, uint8_t dayofweek, uint8_t hour, uint8_t minute, uint8_t second);
extern void ds1307_getdate(uint8_t *year, uint8_t *month, uint8_t *day,uint8_t *dayofweek, uint8_t *hour, uint8_t *minute, uint8_t *second);