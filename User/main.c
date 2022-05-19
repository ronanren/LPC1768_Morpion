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

#include "global.h"
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>

// Morpion

// Initialise les broches pour la gestion de la mémoire par l’I2C0 et les boutons poussoirs
void pin_Configuration()
{
		// Gestion du pin connect bloc pour la mémoire par l'I2C0
		LPC_PINCON->PINSEL1 |= (1<<22); // P0.27 => 01 sur 23:22 et P0.28 => 01 sur 25:24 
		LPC_PINCON->PINSEL1 |= (1<<24);
		// Gestion des boutons poussoirs
		// LPC_PINCON->PINSEL4 déja à 0 car P2.10 => 00 sur 21:20 et P2.11 => 00 sur 23:22
		// Initialisation du GPIO
		GPIO_SetDir(2, (1 << 10)|(1 << 11), 0); // Port 2 en input pour changer la direction avec (1 << 10)|(1 << 11)
}

void write_lcd(){
	uint8_t scorebleu;
	i2c_eeprom_read(0, &scorebleu, 2);
	sprintf(chaine,"Score Bleu : %d", scorebleu);
	LCD_write_english_string(32,10,chaine,White,Blue);
	sprintf(chaine,"Score Rouge : 0");
	LCD_write_english_string(32,30,chaine,White,Blue);
	dessiner_rect(10,60,74,74,2,1,Black,cases[0]); // |1|2|3|
	dessiner_rect(84,60,74,74,2,1,Black,cases[1]);  // |4|5|6|
	dessiner_rect(158,60,74,74,2,1,Black,cases[2]); // |7|8|9|
	dessiner_rect(10,134,74,74,2,1,Black,cases[3]);
	dessiner_rect(84,134,74,74,2,1,Black,cases[4]); 
	dessiner_rect(158,134,74,74,2,1,Black,cases[5]);
	dessiner_rect(10,208,74,74,2,1,Black,cases[6]);
	dessiner_rect(84,208,74,74,2,1,Black,cases[7]);
	dessiner_rect(158,208,74,74,2,1,Black,cases[8]);
}

void updatejoueur(int idcase){
	if (lastjoueur == Blue && cases[idcase] == White){
			cases[idcase] = Red;
			lastjoueur = Red;
	}
	else if (cases[idcase] == White) {
		cases[idcase] = Blue;
		lastjoueur = Blue;
	}
}

void verifgagnant(){
	uint8_t scorebleu;
	i2c_eeprom_read(0, &scorebleu, 1);
	// Verification ligne 1
	if (cases[0] != White && cases[0] == cases[1] && cases[0] == cases[2]){
		if (cases[0] == Blue){
			sprintf(chaine,"Joueur Bleu a gagne");
			scorebleu = scorebleu + 1;
			i2c_eeprom_write(0, &scorebleu, sizeof(scorebleu));
		} else {
			sprintf(chaine,"Joueur Rouge a gagne");
		}
		lcd_clear(cases[0]);
		LCD_write_english_string(40,120,chaine,White,cases[0]);
		gagne = '1';
	}
	// Verification ligne 2
	if (cases[3] != White && cases[3] == cases[4] && cases[3] == cases[5]){
		if (cases[3] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[3]);
		LCD_write_english_string(40,120,chaine,White,cases[3]);
		gagne = '1';
	}
	// Verification ligne 3
	if (cases[6] != White && cases[6] == cases[7] && cases[6] == cases[8]){
		if (cases[6] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[6]);
		LCD_write_english_string(40,120,chaine,White,cases[6]);
		gagne = '1';
	}
	
	// Verification colonne 1
	if (cases[0] != White && cases[3] == cases[0] && cases[0] == cases[6]){
		if (cases[0] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[0]);
		LCD_write_english_string(40,120,chaine,White,cases[0]);
		gagne = '1';
	}
	// Verification colonne 2
	if (cases[1] != White && cases[4] == cases[1] && cases[1] == cases[7]){
		if (cases[1] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[1]);
		LCD_write_english_string(40,120,chaine,White,cases[1]);
		gagne = '1';
	}
	// Verification colonne 3
	if (cases[2] != White && cases[5] == cases[2] && cases[2] == cases[8]){
		if (cases[2] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[2]);
		LCD_write_english_string(40,120,chaine,White,cases[2]);
		gagne = '1';
	}
	
	// Verification diagonale gauche à droite
	if (cases[0] != White && cases[4] == cases[0] && cases[0] == cases[8]){
		if (cases[0] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[0]);
		LCD_write_english_string(40,120,chaine,White,cases[0]);
		gagne = '1';
	}
	// Verification diagonale droite à gauche
	if (cases[2] != White && cases[4] == cases[2] && cases[2] == cases[6]){
		if (cases[2] == Blue)
			sprintf(chaine,"Joueur Bleu a gagne");
		else
			sprintf(chaine,"Joueur Rouge a gagne");
		lcd_clear(cases[2]);
		LCD_write_english_string(40,120,chaine,White,cases[2]);
		gagne = '1';
	}
	
	// Verification égalité
	if (cases[0] != White && cases[1] != White && cases[2] != White && cases[3] != White && cases[4] != White && cases[5] != White && cases[6] != White && cases[7] != White && cases[8] != White){
		sprintf(chaine,"Egalite");
		lcd_clear(Grey);
		LCD_write_english_string(90,120,chaine,Black,Grey);
		gagne = '1';
	}
}

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	  
		int n;
		int lengthdata;
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
		data = 0;
//		i2c_eeprom_write(slaveAddress, &data, lengthdata);
		i2c_eeprom_read(0, &datarecieve, 1); // slaveaddress a 0 pour le score du joueur bleu
		// i2c_eeprom_write(0, &data, sizeof(data));
	
	  // Init(); // init variables globales et pinsel pour IR => à faire
	
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		timer1_init();
		// affichage sur l'écran de 6 carrés de couleur blanche et de deux chaine de caractères pour le score du joueur bleu et rouge
		write_lcd();
		
	  touch_init(); // init pinsel tactile et init tactile; à ne laisser que si vous utilisez le tactile
	  
    while(1){
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
