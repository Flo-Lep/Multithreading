/*
 * timer.c
 * Created on: April 2, 2023
 * Author: Florentin LEPELTIER
 */

#ifndef _TIMER_H_
#define _TIMER_H_

typedef struct TimerAttributes Timer;

/*CONSTRUCTOR*/
extern Timer* TIMER_create(void);

/*DESTRUCTOR*/
extern void TIMER_destroy(Timer* p);

/*METHODS*/
extern void TIMER_init(Timer* p, int time_in_seconds);
extern void TIMER_start(Timer* p);
extern void TIMER_STOP(Timer *p);

#endif /*_TIMER_H_*/
