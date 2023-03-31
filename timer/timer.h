#ifndef _TIMER_
#define _TIMER_

typedef struct TimerAttributes Timer;

/*CONSTRUCTOR*/
extern Timer* TIMER_create(void);

/*DESTRUCTOR*/
extern void TIMER_destroy(Timer* p);

/*METHODS*/
extern void TIMER_init(Timer* p);
extern void TIMER_start(Timer* p);

#endif /*_TIMER_*/
