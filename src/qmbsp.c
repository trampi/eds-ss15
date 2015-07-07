/*****************************************************************************
* Product: Board Support Package (BSP) for the QM examples
* Keil ARM MDK  2300 
* Dr. Ron Barker 
*****************************************************************************/
#include "qmbsp.h"
#include "LCD.h"

#include <stdio.h>
#include <stdlib.h>



/*BSP Init for the MC2300 */

void BSP_Init( ) {
	
	// initialize drivers
	Timer0_Init();
	Timer1_Init();
	AD_Wheel_Init();
	Button_Init();
	LED_Init();
	RtcInit();
	//COM
  uart_init_0 ( );
  lcd_init();
  lcd_clear();
  set_cursor (0, 0);
}



int _kbhit(void ) {

	int i;
	 i = 0xFF;
	 return(i);
}


int _getch()

{
	 FILE *f;
 return	 ( fgetc(  f) );
}
	
/*..........................................................................*/
/* this function is used by the QP embedded systems-friendly assertions */
void Q_onAssert(char const * const file, int line) {
    printf("Assertion failed in %s, line %d", file, line);
    fflush(stdout);
    _sys_exit(-1);
}
/*..........................................................................*/
/* Application specific callbacks from the framework  */
void QF_onCleanup(void)	  {

	 ;

	 }

void QF_onIdle(void)	  {

	
	 ;

	 }
void QF_onStartup(void)	  {

	
	 ;

	 }
