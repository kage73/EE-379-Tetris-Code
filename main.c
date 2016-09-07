#include "GLCD.h"                               /* GLCD function prototypes */
#include "lpc17xx.h"
#include "tetris.h"
#include "draw.h"
#include "piece.h"
#include "controls.h"

#include <time.h> 
#include <stdlib.h>  

int reset;

int main() {
	reset = 0;
	
	SystemInit();
	
	LPC_GPIOINT->IO2IntEnR |= 1 << 10; 
	NVIC_EnableIRQ(EINT3_IRQn); 
	
	GLCD_Init();
	GLCD_Clear(Black);

	tetris_initPieces();
	
	while(1) {
		tetris_newTetris();
		reset = 0;
	
	
		while(!tetris_hasLost()) {
			tetris_update();
			tetris_render();
		}
		
		GLCD_SetTextColor(White);
		GLCD_DisplayString(5, 5, "YOU LOSE");
		while(!reset) {}		
			
	}
}

void EINT3_IRQHandler (void) {
    LPC_GPIOINT->IO2IntClr |= 1 << 10; 
    reset = 1;
}
