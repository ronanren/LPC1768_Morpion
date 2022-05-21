#include "touch/ili_lcd_general.h"
#include "touch/lcd_api.h"
#include "touch/touch_panel.h"
#include "global.h"
#include "memoire.h"
#include "touch/lcd_api.h"

void dessiner_ligne(unsigned int x, unsigned int y, unsigned int l,unsigned int e, char orientation, unsigned short color)
{
	int i,j;
	if(orientation=='v')
	{
		for(j=y;j<=y+l;j++)
		{
			lcd_SetCursor(x,j);//on place le curseur à la bonne position
			rw_data_prepare();
			for(i=0;i<=e;i++)
			{
				write_data(color);//on trace un point et on passe à la position suivante
			}
		}
	}
	else//orientation='h'
	{
		for(j=y;j<=y+e;j++)
		{
			lcd_SetCursor(x,j);//on place le curseur à la bonne position
			rw_data_prepare();
			for(i=0;i<=l;i++)
			{
				write_data(color);//on trace un point et on passe à la position suivante
			}
		}
	}
}

void dessiner_rect(unsigned int x, unsigned int y, unsigned int lng, unsigned int lrg, unsigned int e, unsigned short plein, unsigned short e_color, unsigned short bg_color)
{
	//dessiner fond
	if(plein==1)
	{
		dessiner_ligne(x,y,lng,lrg,'h',bg_color);
	}
	
	//dessiner bordures
	dessiner_ligne(x,y,lng,e,'h',e_color);
	dessiner_ligne(x+lng-e,y,lrg,e,'v',e_color);
	dessiner_ligne(x,y+lrg-e,lng,e,'h',e_color);
	dessiner_ligne(x,y,lrg,e,'v',e_color);
}

void write_lcd(){
	uint8_t resultat_bleu;
	uint8_t resultat_rouge;
	dessiner_rect(10,60,74,74,2,1,Black,cases[0]); //  |1|2|3|
	dessiner_rect(84,60,74,74,2,1,Black,cases[1]);  // |4|5|6|
	dessiner_rect(158,60,74,74,2,1,Black,cases[2]); // |7|8|9|
	dessiner_rect(10,134,74,74,2,1,Black,cases[3]);
	dessiner_rect(84,134,74,74,2,1,Black,cases[4]); 
	dessiner_rect(158,134,74,74,2,1,Black,cases[5]);
	dessiner_rect(10,208,74,74,2,1,Black,cases[6]);
	dessiner_rect(84,208,74,74,2,1,Black,cases[7]);
	dessiner_rect(158,208,74,74,2,1,Black,cases[8]);
	
	// Lecture en mémoire I2C du resultat_bleu à l'adresse 0 et du resultat_bleu à l'adresse 1
	i2c_eeprom_read(0, &resultat_bleu, sizeof(resultat_bleu));
	i2c_eeprom_read(1, &resultat_rouge, sizeof(resultat_rouge));
	
	// Affichage des scores lu dans la mémoire I2C
	sprintf(chaine,"Score Bleu : %d  ", resultat_bleu);
	LCD_write_english_string(32,10,chaine,White,Blue);
	sprintf(chaine,"Score Rouge : %d  ", resultat_rouge);
	LCD_write_english_string(32,30,chaine,White,Blue);
}
