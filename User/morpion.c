#include "morpion.h"
#include "memoire.h"
#include "global.h"
#include "affichagelcd.h"
#include "touch/ili_lcd_general.h"

// Change la couleur du joueur de façon alternée
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

// Remettre à 0 les scores au sein de la mémoire
void reset_score(){
	uint8_t resultat_bleu = 0;
  uint8_t resultat_rouge = 0;
	i2c_eeprom_write(0, &resultat_bleu, sizeof(resultat_bleu));
	i2c_eeprom_write(1, &resultat_rouge, sizeof(resultat_rouge));
	write_lcd();
}

// Vérifier si un joueur a gagné la partie
void verifgagnant(){
	uint8_t resultat_bleu;
	uint8_t resultat_rouge;
	char gagnant = 'E'; // égalité de base
	// Verification des lignes, colonnes et diagonales 
	if ((cases[0] != White && cases[0] == cases[1] && cases[0] == cases[2]) // Verification ligne 1
			|| (cases[0] != White && cases[3] == cases[0] && cases[0] == cases[6]) // Verification colonne 1
		  || (cases[0] != White && cases[4] == cases[0] && cases[0] == cases[8])){ // Verification diagonale gauche à droite
		if (cases[0] == Blue){
			sprintf(chaine,"Joueur Bleu a gagne");
			gagnant = 'B';
		} else {
			sprintf(chaine,"Joueur Rouge a gagne");
			gagnant = 'R';
		}
		lcd_clear(cases[0]);
		LCD_write_english_string(40,120,chaine,White,cases[0]);
		gagne = '1';
	}
	if (cases[3] != White && cases[3] == cases[4] && cases[3] == cases[5]){ // Verification ligne 2
		if (cases[3] == Blue){
			sprintf(chaine,"Joueur Bleu a gagne");
			gagnant = 'B';
		} else {
			sprintf(chaine,"Joueur Rouge a gagne");
			gagnant = 'R';
		}
		lcd_clear(cases[3]);
		LCD_write_english_string(40,120,chaine,White,cases[3]);
		gagne = '1';
	}
	if ((cases[6] != White && cases[6] == cases[7] && cases[6] == cases[8]) // Verification ligne 3
		  || (cases[1] != White && cases[4] == cases[1] && cases[1] == cases[7])){ // Verification colonne 2
		if (cases[7] == Blue){
			sprintf(chaine,"Joueur Bleu a gagne");
			gagnant = 'B';
		} else {
			sprintf(chaine,"Joueur Rouge a gagne");
			gagnant = 'R';
		}
		lcd_clear(cases[7]);
		LCD_write_english_string(40,120,chaine,White,cases[7]);
		gagne = '1';
	}
	if ((cases[2] != White && cases[5] == cases[2] && cases[2] == cases[8]) // Verification colonne 3
			|| (cases[2] != White && cases[4] == cases[2] && cases[2] == cases[6])){ // Verification diagonale droite à gauche
		if (cases[2] == Blue){
			sprintf(chaine,"Joueur Bleu a gagne");
			gagnant = 'B';
		} else {
			sprintf(chaine,"Joueur Rouge a gagne");
			gagnant = 'R';
		}
		lcd_clear(cases[2]);
		LCD_write_english_string(40,120,chaine,White,cases[2]);
		gagne = '1';
	}
	// Verification égalité
	if (gagne == '0' && cases[0] != White && cases[1] != White && cases[2] != White && cases[3] != White && cases[4] != White && cases[5] != White && cases[6] != White && cases[7] != White && cases[8] != White){
		sprintf(chaine,"Egalite");
		lcd_clear(Grey);
		LCD_write_english_string(90,120,chaine,Black,Grey);
		gagne = '1';
	}
	// Gestion de l'incrémentation des scores et de l'écriture des scores en mémoire si il y a un gagnant
	if (gagne == '1'){
		if (gagnant == 'R'){
			i2c_eeprom_read(1, &resultat_rouge, sizeof(resultat_rouge));
			resultat_rouge++;
			i2c_eeprom_write(1, &resultat_rouge, sizeof(resultat_rouge));
		} else if (gagnant == 'B') {
			i2c_eeprom_read(0, &resultat_bleu, sizeof(resultat_bleu));
			resultat_bleu++;
			i2c_eeprom_write(0, &resultat_bleu, sizeof(resultat_bleu));
		}
	}
}