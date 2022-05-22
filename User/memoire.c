#include "lpc17xx_i2c.h"
#include "memoire.h"

void init_i2c_eeprom(){
		I2C_Init(LPC_I2C0, 500000); // Configuration de la m�moire � 500Khz
		I2C_Cmd(LPC_I2C0, ENABLE); // Autoriser les �changes I2C0
}

void i2c_eeprom_write(uint16_t addr, uint8_t *data, int length)
{
	int i;
	uint8_t data_to_write[255];
	I2C_M_SETUP_Type config; // config I2C
	
	// 0101 | addr >> 8 pour ne r�cup�rer que les 3 bits de poids fort de l'adresse de m�moire
	config.sl_addr7bit = 0x50 | (addr >> 8); 

	data_to_write[0] = ((addr) & (0xFF)); // R�cup�ration des lignes de la m�moire � transmettre dans les donn�es
	for(i=0; i < length; i++)
	{
		data_to_write[i+1] = data[i]; // R�cup�ration des donn�es � �crire
	}
	
	config.tx_data = data_to_write; // Donn�es � �crire
	config.tx_count = 0; // Compteur des donn�es � transmettre � 0
	config.tx_length = length + 1; // Taille de l'adresse + les donn�es
	// Nombre de retransmission � z�ro de base et maximum 3
	config.retransmissions_max = 3;
	config.retransmissions_count = 0;
	config.status = 0;
	
	I2C_MasterTransferData(LPC_I2C0, &config,I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, uint8_t *data, int length)
{
	I2C_M_SETUP_Type config; // config I2C
	uint8_t addr_ligne = addr & 0xFF;
	config.sl_addr7bit = 0x50 | (addr >> 8); // 0101 | addr >> 8 pour ne r�cup�rer que les 3 bits de poids fort de l'adresse de m�moire
		
	config.tx_data = &addr_ligne;
	config.tx_count = 0;
	config.tx_length = 1;
	
	config.rx_data = data;
	config.rx_length = length;

	// Nombre de retransmission � z�ro de base et maximum 3
	config.retransmissions_max = 3;
	config.retransmissions_count = 0;
	config.status = 0;
	
	I2C_MasterTransferData(LPC_I2C0, &config, I2C_TRANSFER_POLLING);
}