#include "global.h"
#include "constantes.h"
#include "lpc17xx_i2c.h"
#include "timer1.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg_default.h"
#include "affichagelcd.h"
#include "touch\ili_lcd_general.h"

// Initialisation d'un timer1 qui va partir en interruption toute les 2.5ms avec une pr�cision de 500us
void timer1_init(){
		int cpt_LCD = 0;
	
		// declaration des structures de configuration
		PINSEL_CFG_Type maconfig; // pour pin connect bloc 
		TIM_TIMERCFG_Type maconfigtimer ; // pour timer mode et precision
		TIM_MATCHCFG_Type maconfigmatch ; // pour timer match
	
		// Programmation du NVIC
		NVIC_EnableIRQ(TIMER1_IRQn);
	
		// remplissage pour P1.28 sur MAT0.0
		maconfig.Portnum = PINSEL_PORT_1;
		maconfig.Pinnum = PINSEL_PIN_28;
  	maconfig.Funcnum = PINSEL_FUNC_3;
	  maconfig.Pinmode = 0;
		maconfig.OpenDrain = PINSEL_PINMODE_NORMAL;
		// appel de la fonction qui va initialiser les registres
		PINSEL_ConfigPin(&maconfig);
	
		// remplissage pour choisir le mode timer et la precision
		maconfigtimer.PrescaleOption = TIM_PRESCALE_USVAL; // l'unit� du prescaler est en ms
    maconfigtimer.PrescaleValue = 500; // On met le prescaler � 500us
		// appel de la fonction qui va initialiser les registres
		TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &maconfigtimer);
	
		// remplissage pour choisir les actions quand �a match
		maconfigmatch.ExtMatchOutputType = TIM_EXTMATCH_NOTHING; // inverse la sortie a chaque match
		maconfigmatch.IntOnMatch = ENABLE; // Interruption generee quand ca match
		maconfigmatch.StopOnMatch = DISABLE;
		maconfigmatch.MatchChannel = 0; // on utilise MR0
		maconfigmatch.MatchValue = 5; // correspond a la duree pour un match de 2.5ms
		maconfigmatch.ResetOnMatch = ENABLE; // remet TC a 0 quand ca match
		// appel de la fonction qui va initialiser les registres
		TIM_ConfigMatch(LPC_TIM1, &maconfigmatch);
		// lancement du timer-compteur 
		TIM_Cmd(LPC_TIM1, ENABLE);
}

void TIMER1_IRQHandler(void){
	cpt_LCD++; // gestion d'un compteur pour scruter le port P0.19 tout les 25ms
	if (cpt_LCD == 10){
		cpt_LCD=0;
		// Vérification si il y a un touch� sur l'�cran tactile
		if ((((LPC_GPIO0->FIOPIN) >> 19) & (0x01)) == 0){
			flagtacheclavier = '1';
		}
		// Vérification d'un appui sur le bouton KEY1 avec le GPIO
		if (((LPC_GPIO2->FIOPIN >> 11) & (0x01)) == 0){
			flagbouton = '1';
		}
	}
	
	LPC_TIM1->IR = 1 << 0;
}