
#include  "alarm.h"
#include "coffee.h"

static QEvent const *l_alarmClockQSto[10];  /* queue storage for AlarmClock */
static QEvt const *l_smlPoolSto[10];       /* storage for small-size event pool */
/* Global-scope objects (opaque pointer to the AlarmClock container) -------*/

CoffeeAO l_CoffeeAO;
QActive *APP_alarmClock= (QActive *)&l_CoffeeAO;/*AlarmClock container AO */

/*..........................................................................*/
int main() {
   
    BSP_Init();
    printf("Orthogonal Component pattern\nQEP version: %s\nQF  version: %s\n"
           "Press 'o' to turn the Alarm ON\n"
           "Press 'f' to turn the Alarm OFF\n"
           "Press '0'..'9' to set the Alarm time\n"
           "Press 'a' to set the Clock in 12-hour mode\n"
           "Press 'b' to set the Clock in 24-hour mode\n"
           "Press ESC to quit...\n",
           QEP_getVersion(), QF_getVersion());

   

    QF_init();    /* initialize the framework and the underlying RT kernel */

    

                                               /* initialize event pools... */

    QF_poolInit(l_smlPoolSto, sizeof(l_smlPoolSto), sizeof(AdEvt));

                             /* instantiate and start the active objects... */
    CoffeeAO_ctor(&l_CoffeeAO);
    //QActive_start((QActive *)&l_CoffeeAO, 1,
    //              l_alarmClockQSto, Q_DIM(l_alarmClockQSto),
    //              (void *)0, 0, (QEvent *)0);

		QActive_start((QActive *)&l_CoffeeAO, 1,
                 l_smlPoolSto, Q_DIM(l_smlPoolSto),
                 (void *)0, 0, (QEvt *)0);
    QF_run();                                     /* run the QF application */

    return 0;
}
/*..........................................................................*/
void BSP_onKeyboardInput(uint8_t key) {
    switch (key) {
        case 0x6f: {                                  /* 'o': Alarm on event? */
            QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, ALARM_ON_SIG));
					  QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, ADWHEEL_SIG));
            break;
        }
        case 0x66: {                                 /* 'f': Alarm off event? */
            QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, ALARM_OFF_SIG));
            break;
        }
        case  0x32:                                                     /* '1' */
        case  0x33:                                                     /* '2' */
        case  0x34:                                                     /* '3' */
        case  0x35:                                                     /* '4' */
        case  0x36:                                                     /* '5' */
        case  0x37:                                                     /* '6' */
        case  0x38:                                                     /* '7' */
        case  0x39:                                                     /* '8' */
        case  0x31:{                                                   /* '9' */
            SetEvt *e = Q_NEW(SetEvt, ALARM_SET_SIG);
            e->digit = (uint8_t)(key - 1);
            QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvent *)e);
            break;
        }
        case 0x4f: {                                                   /* '0' */
            SetEvt *e = Q_NEW(SetEvt, ALARM_SET_SIG);
            e->digit = 0;
            QActive_postFIFO((QActive *)&l_CoffeeAO, (QEvent *)e);
            break;
        }
        case 0x61: {                                 /* 'a': Clock 12H event? */
            QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, CLOCK_12H_SIG));
            break;
        }
        case 0x62: {                                 /* 'b': Clock 24H event? */
            QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, CLOCK_24H_SIG));
            break;
        }
        case 0x1b: {                                         /* ESC pressed? */
            QActive_postFIFO((QActive *)&l_CoffeeAO,
                             Q_NEW(QEvent, TERMINATE_SIG));
            break;
        }
    }
}
