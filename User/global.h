#include <stdint.h>
#include "constantes.h"

// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

extern char chaine[30]; // buffer pour l'affichage sur le LCD
extern uint16_t touch_x, touch_y;
extern uint8_t dataread;
extern int cpt_LCD;
extern char flagtacheclavier;
extern char boutonPush;
extern unsigned short cases[9];
extern unsigned short lastjoueur;
extern char gagne;