#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>

// mettez ici toutes les déclarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;

int cpt_LCD;
char flagtacheclavier;
char flagbouton;
int refreshLCD;
unsigned short cases[9];
unsigned short lastjoueur;
char gagne;