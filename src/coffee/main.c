
#include  "alarm.h"
#include "coffee.h"

static QEvt const   *l_smlPoolSto_0[24];       /* storage for small-size event pool */
static SetEvt const *l_smlPoolSto_1[24];       /* storage for small-size event pool */
static AdEvt const  *l_smlPoolSto_2[24];       /* storage for small-size event pool */
static RtcEvt const *l_smlPoolSto_3[24];       /* storage for small-size event pool */

/* Global-scope objects (opaque pointer to the AlarmClock container) -------*/

CoffeeAO l_CoffeeAO;
QActive *APP_alarmClock= (QActive *)&l_CoffeeAO;/*AlarmClock container AO */

/*..........................................................................*/
int main() {
		/* initialize the framework and the underlying RT kernel */
    QF_init();
		
		/* initialize event pools... */
		QF_poolInit(l_smlPoolSto_0, sizeof(l_smlPoolSto_0), sizeof(QEvt));
		QF_poolInit(l_smlPoolSto_1, sizeof(l_smlPoolSto_1), sizeof(SetEvt));
		QF_poolInit(l_smlPoolSto_3, sizeof(l_smlPoolSto_3), sizeof(RtcEvt));
 
		CoffeeAO_ctor(&l_CoffeeAO);
    //QActive_start((QActive *)&l_CoffeeAO, 1,
    //              l_alarmClockQSto, Q_DIM(l_alarmClockQSto),
    //              (void *)0, 0, (QEvt *)0);
		/*
		QActive_start((QActive *)&l_CoffeeAO, 1,
                  l_smlPoolSto_0, Q_DIM(l_smlPoolSto_0),
                 (void *)0, 0, (QEvt *)0);
	
		QActive_start((QActive *)&l_CoffeeAO, 2,
                  (const QEvt**)l_smlPoolSto_1, Q_DIM(l_smlPoolSto_1),
                 (void *)0, 0, (QEvt *)0);
		*/
		QActive_start((QActive *)&l_CoffeeAO, 3,
                  (const QEvt**)l_smlPoolSto_3, Q_DIM(l_smlPoolSto_3),
                 (void *)0, 0, (QEvt *)0);
		BSP_Init();
    
		printf("%i\n", sizeof(QEvt));
		printf("%i\n", sizeof(SetEvt));
		printf("%i\n", sizeof(AdEvt));
		printf("%i\n", sizeof(RtcEvt));

		QF_run();                                     /* run the QF application */

    return 0;
}
/*..........................................................................*/
//void BSP_onKeyboardInput(uint8_t key) {
//    switch (key) {
//        case 0x6f: {                                  /* 'o': Alarm on event? */
//            QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, ALARM_ON_SIG));
//					  QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, ADWHEEL_SIG));
//            break;
//        }
//        case 0x66: {                                 /* 'f': Alarm off event? */
//            QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, ALARM_OFF_SIG));
//            break;
//        }
//        case  0x32:                                                     /* '1' */
//        case  0x33:                                                     /* '2' */
//        case  0x34:                                                     /* '3' */
//        case  0x35:                                                     /* '4' */
//        case  0x36:                                                     /* '5' */
//        case  0x37:                                                     /* '6' */
//        case  0x38:                                                     /* '7' */
//        case  0x39:                                                     /* '8' */
//        case  0x31:{                                                   /* '9' */
//            SetEvt *e = Q_NEW(SetEvt, ALARM_SET_SIG);
//            e->digit = (uint8_t)(key - 1);
//            QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvt *)e);
//            break;
//        }
//        case 0x4f: {                                                   /* '0' */
//            SetEvt *e = Q_NEW(SetEvt, ALARM_SET_SIG);
//            e->digit = 0;
//            QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvt *)e);
//            break;
//        }
//        case 0x61: {                                 /* 'a': Clock 12H event? */
//            QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, CLOCK_12H_SIG));
//            break;
//        }
//        case 0x62: {                                 /* 'b': Clock 24H event? */
//            QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, CLOCK_24H_SIG));
//            break;
//        }
//        case 0x1b: {                                         /* ESC pressed? */
//            QActive_postFIFO((QActive *)&l_CoffeeAO,
//                             Q_NEW(QEvt, TERMINATE_SIG));
//            break;
//        }
//    }
//}
//

