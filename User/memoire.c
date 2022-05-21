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
	I2C_M_SETUP_Type master; // Master I2C
	
	// 0b0101 | addr >> 8 pour ne r�cup�rer que les 3 bits de poids fort de l'adresse ( bits de colonnes de la m�moire)
	master.sl_addr7bit = 0x50 | (addr >> 8); // 

	data_to_write[0] = ((addr) & (0xFF)); // R�cup�ration des lignes de la m�moire � transmettre dans les donn�es
	for(i=0; i < length; i++)
	{
		data_to_write[i+1] = data[i]; // R�cup�ration des donn�es � �crire
	}
	
	master.tx_data = data_to_write; // Donn�es � �crire
	master.tx_count = 0; // Compteur des donn�es � transmettre � 0, car processus non commenc�
	master.tx_length = length+1; // Taille de l'adresse + donn�es
	// Non utilis�, car utile pour la lecture
	master.rx_data = NULL;
	master.rx_length = 0;
	master.rx_count = 0;
	// Nombre de retransmission � z�ro de base et maximum 3
	master.retransmissions_max = 3;
	master.retransmissions_count = 0;
	master.status = 0;
	
	I2C_MasterTransferData(LPC_I2C0,&master,I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, uint8_t * data, int length)
{
	I2C_M_SETUP_Type master; // Master I2C
	uint8_t addr_ligne = addr & 0xFF;
		master.sl_addr7bit = 0x50 | (addr >> 8);
			
		master.tx_data = &addr_ligne;
		master.tx_count = 0;
		master.tx_length = 1;
		
		master.rx_data = data;
		master.rx_length = length;

		// Nombre de retransmission � z�ro de base et maximum 3
		master.retransmissions_max = 3;
		master.retransmissions_count = 0;
		master.status = 0;
		
		I2C_MasterTransferData(LPC_I2C0,&master,I2C_TRANSFER_POLLING);		
}