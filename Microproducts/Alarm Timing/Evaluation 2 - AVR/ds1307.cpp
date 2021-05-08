#include "ds1307.h"

uint8_t ds1307_dec2bcd(uint8_t val) {
	return val + 6 * (val / 10);
}