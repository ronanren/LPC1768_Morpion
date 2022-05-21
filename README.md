# LPC1768_Morpion

* [1. Morpion](#morpion)
    * [1.1. Déclaration et sens des variables](#variables)
    * [1.2 Traitement du programme principale](#traitement)
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
Variable globale en tant que flag lors de la vérification du gagnant.'1' lorsque il y a un gagnant et ainsi, l'affichage d'un écran du gagnant s'affiche.

<a name="traitement"></a>
## 1.2 Traitement du programme principale

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
Mise en place du timer avec intéruption toute les 10ms puis vérification toute les 100ms à l'aide d'un compteur le touché sur l'écran tactile et l'appui sur un bouton de la carte mère.

<a name="Utilisation"></a>
# 2. Utilisation

sometext