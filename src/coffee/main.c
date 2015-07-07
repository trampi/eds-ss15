
#include  "alarm.h"
#include "coffee.h"

static QEvt const   *l_smlPoolSto_4[24];       /* Events 4 Byte */
static SetEvt const *l_smlPoolSto_6[24];       /* 6 Byte */
static RtcEvt const *l_smlPoolSto_14[24];       /* 12 Byte*/

/* Global-scope objects (opaque pointer to the AlarmClock container) -------*/

CoffeeAO l_CoffeeAO;
QActive *APP_alarmClock= (QActive *)&l_CoffeeAO;/*AlarmClock container AO */

/*..........................................................................*/
int main() {
	
		/* initialize the framework and the underlying RT kernel */
    QF_init();
		
		/* initialize event pools... have to be initialized in increasing size order */
		QF_poolInit(l_smlPoolSto_4, sizeof(l_smlPoolSto_4), sizeof(QEvt));
		QF_poolInit(l_smlPoolSto_6, sizeof(l_smlPoolSto_6), sizeof(SetEvt));
		QF_poolInit(l_smlPoolSto_14, sizeof(l_smlPoolSto_14), sizeof(RtcEvt));
		
		/*create the coffe active object*/
		CoffeeAO_ctor(&l_CoffeeAO);
	
		/*start active object*/
		QActive_start((QActive *)&l_CoffeeAO, 3,
                  (const QEvt**)l_smlPoolSto_14, Q_DIM(l_smlPoolSto_14),
                 (void *)0, 0, (QEvt *)0);
									
    /*initialize bsp after pools*/											
		BSP_Init();
    
	//printf("%i\n", sizeof(QEvt));
	//printf("%i\n", sizeof(SetEvt));
	//printf("%i\n", sizeof(AdEvt));
	//printf("%i\n", sizeof(RtcEvt));

		/* run the QF application */
		QF_run();                                     

    return 0;
}

