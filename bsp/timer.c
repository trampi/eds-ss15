#include <stdio.h>
#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include "qp_port.h"

/* Timer0 IRQ: Executed periodically                                          */
__irq void T0_IRQHandler (void) {
 
	QF_INT_ENABLE();
	QF_tick();
	QF_INT_DISABLE();
	
  T0IR        = 1;                      /* Clear interrupt flag               */
  VICVectAddr = 0;                      /* Acknowledge Interrupt              */
}


void  Timer0_Init(void )  {
	
	
  /* Enable and setup timer interrupt, start timer                            */
  T0MR0         = 11999;                       /* 1msec = 12000-1 at 12.0 MHz */
  T0MCR         = 3;                           /* Interrupt and Reset on MR0  */
  T0TCR         = 1;                           /* Timer0 Enable               */
  VICVectAddr4  = (unsigned long)T0_IRQHandler;/* Set Interrupt Vector        */
  VICVectCntl4  = 14;                          /* use it for Timer0 Interrupt */
  VICIntEnable  = (1  << 4);                   /* Enable Timer0 Interrupt     */
	
}

/* Timer0 IRQ: Executed periodically                                          */
__irq void T1_IRQHandler (void) {

	
  AD0CR |= 0x01000000;                  /* Start A/D Conversion               */
  T1IR        = 1;                      /* Clear interrupt flag               */
  VICVectAddr = 0;                      /* Acknowledge Interrupt              */
	
}

void Timer1_Init(void )  {
	
	
  /* Enable and setup timer interrupt, start timer                            */
  T1MR0         = 11999 * 200;                       /* 1msec = 12000-1 at 12.0 MHz */
  T1MCR         = 3;                           /* Interrupt and Reset on MR0  */
  T1TCR         = 1;                           /* Timer0 Enable               */
  VICVectAddr5  = (unsigned long)T1_IRQHandler;/* Set Interrupt Vector        */
  VICVectCntl5  = 15;                          /* use it for Timer1 Interrupt */
  VICIntEnable  = (1  << 5);                   /* Enable Timer1 Interrupt     */

	
}
