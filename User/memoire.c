#include "memoire.h"

void init_i2c_eeprom(){
		I2C_Init(LPC_I2C0, 500000); // Configuration de la mémoire à 500Khz
		I2C_Cmd(LPC_I2C0, ENABLE); // Autoriser les échanges I2C0
}

void i2c_eeprom_write(uint16_t addr, t_resultat* data, int length){
		I2C_M_SETUP_Type setupi2c;
		struct datai2c {
			uint8_t addr;
			t_resultat resultat;
		};
		struct datai2c datai2c;
		datai2c.addr = (uint8_t) addr;
		datai2c.resultat = *data;
		// Gestion du Slave ID puis du Page Select => 1010 ABC0
		setupi2c.sl_addr7bit = (1 << 6) | (1 << 4) | (((addr >> 10) & 1) << 2) | (((addr >> 9) & 1) << 1) | (((addr >> 8) & 1) << 0);
		// 8 derniers bits et les données
		setupi2c.tx_data = (uint8_t*) &datai2c;
		setupi2c.tx_length = sizeof(datai2c);
		setupi2c.rx_length = 0;
		I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, t_resultat* data, int length){
		I2C_M_SETUP_Type setupi2c;
		uint8_t addr8 = (uint8_t) addr;
		// Gestion du Slave ID puis du Page Select
		setupi2c.sl_addr7bit = (1 << 6) | (1 << 4) | (((addr >> 10) & 1) << 2) | (((addr >> 9) & 1) << 1) | (((addr >> 8) & 1) << 0);
		setupi2c.tx_data = (uint8_t *) &addr8;
		setupi2c.tx_length = sizeof(addr8);
		setupi2c.rx_length = length;
		setupi2c.rx_data = (uint8_t *) data;
		I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
}