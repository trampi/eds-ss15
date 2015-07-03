#include <LPC23xx.H>                    /* LPC23xx definitions                */
#include <cstdio>
#include "coffee.h"
#include "qf.h"
#include "qp_port.h"  

extern CoffeeAO l_CoffeeAO;
static AdEvt ad_evt;

/* A/D IRQ: Executed when A/D Conversion is done                              */
__irq void ADC_IRQHandler(void) {
	ad_evt.val = (AD0DR0 >> 6) & 0x3FF;      /* Read Conversion Result             */
	if(&l_CoffeeAO != 0) {
		QF_INT_ENABLE();
		QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvent *)&ad_evt);
		QF_INT_DISABLE();
	}
  VICVectAddr = 0;                      /* Acknowledge Interrupt              */
}

void AD_Wheel_Init(void )  {
	PCONP        |= (1 << 12);                   /* Enable power to AD block    */
  PINSEL1       = 0x4000;                      /* AD0.0 pin function select   */
  AD0INTEN      = (1 <<  0);                   /* CH0 enable interrupt        */
  AD0CR         = 0x00200301;                  /* Power up, PCLK/4, sel AD0.0 */
  VICVectAddr18 = (unsigned long)ADC_IRQHandler;/* Set Interrupt Vector       */
  VICVectCntl18 = 14;                          /* use it for ADC Interrupt    */
  VICIntEnable  = (1  << 18);                  /* Enable ADC Interrupt        */
	ad_evt.super.sig = ADWHEEL_SIG;
	ad_evt.super.poolId_ = 0;	
}

