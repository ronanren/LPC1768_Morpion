#include "global.h"
#include "constantes.h"
#include "lpc17xx_i2c.h"

void init_i2c_eeprom(){
		I2C_Init(LPC_I2C0, 400000); // Configuration de la mémoire à 400Khz
		I2C_Cmd(LPC_I2C0, ENABLE); // Autoriser les échanges I2C0
}

void i2c_eeprom_write(uint16_t addr, uint8_t* data, int length){
		I2C_M_SETUP_Type setupi2c;
		uint8_t addr8 = (uint8_t) addr;
		struct datai2c datai2c;
		datai2c.addr = addr8;
		datai2c.data = *data;
		// Gestion du Slave ID puis du Page Select
		setupi2c.sl_addr7bit = (1 << 6)|(1 << 4)|(((addr >> 10) & 1) << 2)|(((addr >> 9) & 1) << 1)|(((addr >> 8) & 1) << 0);
		setupi2c.tx_data = (uint8_t*) &datai2c;
		setupi2c.tx_length = sizeof(datai2c);
		setupi2c.rx_length = 0;
		I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, uint8_t* data, int length){
		I2C_M_SETUP_Type setupi2c;
		uint8_t addr8 = (uint8_t) addr;
		// Gestion du Slave ID puis du Page Select
		setupi2c.sl_addr7bit = (1 << 6)|(1 << 4);
		setupi2c.tx_data = &addr8;
	  setupi2c.rx_data = data;
		setupi2c.tx_length = sizeof(addr8);
		setupi2c.rx_length = length;
		I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
	  dataread = *setupi2c.rx_data;
}