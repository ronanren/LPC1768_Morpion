#include "pin.h"
#include "lpc17xx_gpio.h"

// Initialise les broches pour la gestion de la m�moire par l�I2C0 et le bouton poussoir KEY1
void pin_Configuration()
{
		// Gestion du pin connect bloc pour la m�moire par l'I2C0
		// P0.27 => 01 sur 23:22 et P0.28 => 01 sur 25:24 
		LPC_PINCON->PINSEL1 |= (1 << 22); // P0.27 -> USB_SDA
		LPC_PINCON->PINSEL1 |= (1 << 24); // P0.27 -> USB_SCL
		// Gestion des boutons poussoirs
		// LPC_PINCON->PINSEL4 d�ja � 0 car P2.10 => 00 sur 21:20 pour le key0 et P2.11 => 00 sur 23:22 pour le key1
		// Initialisation du GPIO
		GPIO_SetDir(2, (1 << 10), 0); // Port 2 en input pour changer la direction avec (1 << 10) avec 0 en input
}