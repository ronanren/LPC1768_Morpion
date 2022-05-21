#include "global.h"
#include "lpc17xx_i2c.h"

void init_i2c_eeprom();
void i2c_eeprom_read(uint16_t addr, uint8_t *data, int length);
void i2c_eeprom_write(uint16_t addr, uint8_t * data, int length);