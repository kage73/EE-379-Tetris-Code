#include <LPC17xx.H>                            /* LPC17xx definitions */
#include "GLCD.h"                               /* GLCD function prototypes */


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)  {

  SystemInit();                                   /* initialize MCU clocks */

  GLCD_Init();                                    /* Initialize the GLCD */
  //GLCD_Clear(White);                              /* Clear the GLCD */
	GLCD_Clear(Black);                              /* Clear the GLCD */
	GLCD_SetBackColor(Black);
GLCD_SetTextColor(Green);
//   GLCD_SetBackColor(Blue);                        /* Set the Back Color */
//   GLCD_SetTextColor(White);                       /* Set the Text Color */
	
	GLCD_DisplayString(2, 0, "  Embedded Systems");
  GLCD_DisplayString(4, 0, " Dr.Praveen Meduri");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(6, 0, "     University       ");
	GLCD_DisplayString(7, 0, "         at           ");
  GLCD_DisplayString(8, 0, "       Buffalo        ");
	
  
	
}
