# LPC1768_Morpion

* [1. Morpion](#morpion)
    * [1.1. Déclaration et sens des variables](#variables)
    * [1.2 Déclaration des fonctions](#fonctions)
    * [1.3 Traitement du programme principale](#traitement)
* [2. Utilisation](#Utilisation)

<a name="morpion"></a>
# 1. Morpion

<a name="variables"></a>
## 1.1. Déclaration et sens des variables

```c
uint8_t resultat_bleu;
uint8_t resultat_rouge;
```

Variables local permettant de stocker le nombre de partie gagné par le joueur bleu et le joueur rouge sur 8 bits.

```c
unsigned short lastjoueur = Red;
```
Variable globale qui permet d'alterner le joueur sur le morpion (chacun leur tour).

```c
unsigned short cases[9];
```
Variable globale qui sauvegarde l'avancement du jeu (couleur des cases du morpion) en mettant White au départ au neuf cases. Les cases sont par la suite soit Blue ou Red.

```c
char gagne = '0';
```
Variable globale en tant que flag lors de la vérification du gagnant. '1' lorsque il y a un gagnant et ainsi, l'affichage de l'écran du gagnant s'affiche.

```c
char flagtacheclavier = '0';
char flagbouton = '0';
``` 
Flags utilisés au sein du handler d'interruption du timer pour alerter une touche sur l'écran et l'appui sur un bouton physique.

<a name="fonctions"></a>
## 1.2 Déclaration des fonctions

Listes des fonctions utilisées pour le morpion séparées dans plusieurs fichiers.

```bash
fonctions
├── affichagelcd.c
│   ├── void dessiner_rect(unsigned int x, unsigned int y, unsigned int lng, unsigned int lrg, unsigned int e, unsigned short plein, unsigned short e_color, unsigned short bg_color); # Dessiner un rectange avec un fond et une bordure
│   ├── void dessiner_ligne(unsigned int x, unsigned int y, unsigned int l,unsigned int e, char orientation, unsigned short color); # Dessiner une ligne
|   └── void write_lcd(); # Dessiner les carrés du morpion avec l'affichage des scores lu en mémoire
├── memoire.c
│   ├── void init_i2c_eeprom(); # Initialisation de la mémoire I2C
│   ├── void i2c_eeprom_read(uint16_t addr, uint8_t *data, int length); # Lecture dans la mémoire I2C
|   └── void i2c_eeprom_write(uint16_t addr, uint8_t * data, int length); # Ecriture dans la mémoire I2C
├── morpion.c
│   ├── void updatejoueur(int idcase); # Permet d'alterner de joueur à chaque tour
│   ├── void reset_score(); # Mettre les scores des joueurs à 0 dans la mémoire I2C
|   └── void verifgagnant(); # Vérifier si un joueur a gagné
├── pin.c
│   └── void pin_Configuration(); # Initialise les broches pour la gestion de la mémoire par l'I2C0 et le bouton poussoir KEY1
├── timer1.c
│   └── void timer1_init(); # Initialisation d'un timer1 qui va partir en interruption toute les 10ms avec une précision de 500us
```

<a name="traitement"></a>
## 1.3 Traitement du programme principale

Explication du programme principale *main.c* dans l'ordre d'exécution

```c
pin_Configuration(); // Active le pin connect bloc pour la mémoire I2C et initialisation du GPIO
```

```c
init_i2c_eeprom(); // Initialisation de la mémoire I2C à 500Khz
```

```c
lcd_Initializtion(); // init du pinsel de l'ecran et init du LCD
```

```c
timer1_init();
```
Mise en place du timer avec intéruption toute les 10ms puis vérification toute les 100ms à l'aide d'un compteur le touché sur l'écran tactile (variable flagtacheclavier) et l'appui sur un bouton de la carte mère (variable flagbouton).

```c
write_lcd();
```
Fonction permettant d'afficher les 9 carrés du morpion et d'afficher les scores du joueur bleu et du joueur rouge lu en mémoire I2C.

```c
touch_init(); // init pinsel tactile et init tactile
```

Boucle infini qui permet de gérér les événements du jeu. 
* Lorsqu'on clique sur le bouton KEY1 sur la carte mère, la fonction reset_score(); est appelée pour mettre à 0 les scores des joueurs au sein de la mémoire I2C.
* Lorsqu'on appuie sur l'écran, on vérifie si l'appui est sur une case vide à coché et on vérifie le gagnant

```c
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
```

<a name="Utilisation"></a>
# 2. Utilisation

sometext