//===========================================================//
// Projet Morpion - IMR1 - ENSSAT - 2022 - Ronan RENOUX						 //
//===========================================================//
// File                : main.c
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"
#include "memoire.h"
#include "timer1.h"
#include "lpc17xx_i2c.h"
#include "pin.h"
#include "morpion.h"

#include "global.h"
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>

// Morpion

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	  
		int n;
		int lengthdata;
		uint8_t resultat_bleu;
		uint8_t resultat_rouge;
		uint8_t data;
		uint8_t datarecieve;
		uint32_t slaveAddress;
		pin_Configuration();
		lastjoueur = Red;
		cases[0] = White;
		cases[1] = White;
		cases[2] = White;
		cases[3] = White;
		cases[4] = White;
		cases[5] = White;
		cases[6] = White;
		cases[7] = White;
		cases[8] = White;
		gagne = '0';
	
		// Gestion de la mémoire I2C
		init_i2c_eeprom();
		// resultat_bleu = 0;
		// resultat_rouge = 0;
		// i2c_eeprom_write(0, &resultat_bleu, sizeof(resultat_bleu));
		// i2c_eeprom_write(1, &resultat_rouge, sizeof(resultat_rouge));
		
	
	  // Init(); // init variables globales et pinsel pour IR => à faire
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		timer1_init();
		// affichage sur l'écran de 6 carrés de couleur blanche et de deux chaine de caractères pour le score du joueur bleu et rouge
		write_lcd();

	  touch_init(); // init pinsel tactile et init tactile; à ne laisser que si vous utilisez le tactile
	  
    while(1){
			if (flagbouton == '1'){
				flagbouton = '0';
				reset_score();
			}
			if (flagtacheclavier == '1'){
				flagtacheclavier = '0';
				touch_read();
				if (gagne == '2'){
					cases[0] = White;
					cases[1] = White;
					cases[2] = White;
					cases[3] = White;
					cases[4] = White;
					cases[5] = White;
					cases[6] = White;
					cases[7] = White;
					cases[8] = White;
					lastjoueur = Red;
					lcd_clear(Blue);
					write_lcd();
					gagne = '0';
				}
				if (gagne == '1'){
					gagne = '2';
				}
				if (gagne == '0'){
					if (touch_x > 600 && touch_x <= 1400 && touch_y > 1000 && touch_y <= 1600){ // carre1
						updatejoueur(0);
						write_lcd();
					} else if (touch_x > 1400 && touch_x <= 2200 && touch_y > 1000 && touch_y <= 1600){ // carre2
						updatejoueur(1);
						write_lcd();
					} else if (touch_x > 2400 && touch_x <= 3400 && touch_y > 1000 && touch_y <= 1600){ // carre3
						updatejoueur(2);
						write_lcd();
					} else if (touch_x > 600 && touch_x <= 1400 && touch_y > 1600 && touch_y <= 2400){ // carre4
						updatejoueur(3);
						write_lcd();
					} else if (touch_x > 1400 && touch_x <= 2200 && touch_y > 1600 && touch_y <= 2400){ // carre5
						updatejoueur(4);
						write_lcd();
					} else if (touch_x > 2400 && touch_x <= 3400 && touch_y > 1600 && touch_y <= 2400){ // carre6
						updatejoueur(5);
						write_lcd();
					} else if (touch_x > 600 && touch_x <= 1400 && touch_y > 2400 && touch_y <= 3200){ // carre7
						updatejoueur(6);
						write_lcd();
					} else if (touch_x > 1400 && touch_x <= 2200 && touch_y > 2400 && touch_y <= 3200){ // carre8
						updatejoueur(7);
						write_lcd();
					} else if (touch_x > 2400 && touch_x <= 3400 && touch_y > 2400 && touch_y <= 3200){ // carre9
						updatejoueur(8);
						write_lcd();
					}
					verifgagnant();
				}
		}
	}
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
