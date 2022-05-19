#include <stdint.h>

typedef enum {jaune,vert,rouge,bleu} touche;

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

struct datai2c {
	uint8_t addr;
	uint8_t data;
};