
#include "button.h"
#include <LPC23xx.H>
#include <stdio.h>
#include "qp_port.h"                /* the port of the QEP event processor */
#include "alarm.h"
#include "coffee.h"

__irq void GPIO_IRQHandler (void);
void button_up(void);
void button_down(void);
extern CoffeeAO l_CoffeeAO;
static QEvt event;
	
void Button_Init()
{
	PINSEL4 &= ~(3 << 20);                       /* Set P2.10 to GPIO           */
	FIO2DIR &= ~(1 << 10);                       /* Set P2.10 to input          */
	IO2_INT_EN_R |= (1 << 10);                      /* Enable rising egde interrupt for P2.10. */
	IO2_INT_EN_F |= (1 << 10);                      /* Enable falling egde interrupt for P2.10. */
	VICVectAddr17 = (unsigned long)GPIO_IRQHandler;/* Set Interrupt Vector       */
	VICVectCntl17 = 13;                          /* use it for ADC Interrupt    */
	VICIntEnable  = (1  << 17);                  /* Enable ADC Interrupt        */
	event.sig = INT_SIG;
	event.poolId_ = 0;	
}

__irq void GPIO_IRQHandler(void)
{
	int rising;
	int i;

	
	for(i = 0; i < 1000; i++);

	rising = FIO2PIN & (1 << 10);        /* Value of P2.10 */

	if(rising)
		button_up();
	else
		button_down();

	IO2_INT_CLR = 1 << 10;					  /* Clear Interrupt                    */
	VICVectAddr = 0;                      /* Acknowledge Interrupt              */

}

void button_up()
{
	if(&l_CoffeeAO != 0) {
		QF_INT_ENABLE();
		QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvent *)&event);
		QF_INT_DISABLE();
	}
}

void button_down()
{
// DOWN!!!!
}

