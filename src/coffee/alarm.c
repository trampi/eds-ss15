/*****************************************************************************
* Model: coffeeAo.qm
* File:  src\coffee/alarm.c
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/* @(/3/2) .................................................................*/
#include "qp_port.h"
#include "alarm.h"

/* @(/2/3) .................................................................*/
void Alarm_ctor(Alarm * me) {
    QFsm_ctor(&me->super, (QStateHandler)&Alarm_initial);
}
/* @(/2/1) .................................................................*/
/* @(/2/1/3) ...............................................................*/
/* @(/2/1/3/0) */
QState Alarm_initial(Alarm * const me, QEvt const * const e) {
    (void)e;               /* avoid compiler warning about unused parameter */
    me->alarm_time = 12*60;
    return Q_TRAN(&Alarm_off);
}
/* @(/2/1/3/1) .............................................................*/
QState Alarm_off(Alarm * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* @(/2/1/3/1) */
        case Q_ENTRY_SIG: {
             /* while in the off state, the alarm is kept in decimal format */
            me->alarm_time = (me->alarm_time/60)*100 + me->alarm_time%60;
            printf("*** Alarm OFF %02ld:%02ld\n",
                me->alarm_time/100, me->alarm_time%100);
            fflush(stdout);
            status_ = Q_HANDLED();
            break;
        }
        /* @(/2/1/3/1) */
        case Q_EXIT_SIG: {
                      /* upon exit, the alarm is converted to binary format */
                        me->alarm_time = (me->alarm_time/100)*60 + me->alarm_time%100;
            status_ = Q_HANDLED();
            break;
        }
        /* @(/2/1/3/1/0) */
        case ALARM_ON_SIG: {
            /* @(/2/1/3/1/0/0) */
            if ((me->alarm_time / 100 < 24) && (me->alarm_time % 100 < 60)) {
                status_ = Q_TRAN(&Alarm_on);
            }
            /* @(/2/1/3/1/0/1) */
            else {
                me->alarm_time = 0;
                printf("*** Alarm reset %02ld:%02ld\n",
                       me->alarm_time/100, me->alarm_time%100);
                status_ = Q_TRAN(&Alarm_off);
            }
            break;
        }
        /* @(/2/1/3/1/1) */
        case ALARM_SET_SIG: {
                      /* while setting, the alarm is kept in decimal format */
                        me->alarm_time = (10 * me->alarm_time
                                          + ((SetEvt const *)e)->digit) % 10000;
                        printf("*** Alarm SET %02ld:%02ld\n",
                               me->alarm_time/100, me->alarm_time%100);
                        fflush(stdout);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_IGNORED();
            break;
        }
    }
    return status_;
}
/* @(/2/1/3/2) .............................................................*/
QState Alarm_on(Alarm * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* @(/2/1/3/2) */
        case Q_ENTRY_SIG: {
            printf("*** Alarm ON %02ld:%02ld\n",
                               me->alarm_time/60, me->alarm_time%60);
                        fflush(stdout);
            status_ = Q_HANDLED();
            break;
        }
        /* @(/2/1/3/2/0) */
        case ALARM_SET_SIG: {
            printf("*** Cannot set Alarm when it is ON\n");
            fflush(stdout);
            status_ = Q_HANDLED();
            break;
        }
        /* @(/2/1/3/2/1) */
        case ALARM_OFF_SIG: {
            status_ = Q_TRAN(&Alarm_off);
            break;
        }
        /* @(/2/1/3/2/2) */
        case TIME_SIG: {
            /* @(/2/1/3/2/2/0) */
            if (((TimeEvt *)e)->current_time == me->alarm_time) {
                printf("ALARM!!!\n");
                /* asynchronously post the event to the container AO */
                QActive_postFIFO(APP_alarmClock, Q_NEW(QEvent, ALARM_SIG));
                status_ = Q_HANDLED();
            }
            else {
                status_ = Q_UNHANDLED();
            }
            break;
        }
        default: {
            status_ = Q_IGNORED();
            break;
        }
    }
    return status_;
}

