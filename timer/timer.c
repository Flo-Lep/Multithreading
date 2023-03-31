#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#include "timer.h"

static void ON_ERROR(char error[]);
static void TIMER_time_elapsed(union sigval val);
static time_t current_time;

/*----------OBJECT ATTRIBUTES----------*/
struct TimerAttributes{
	timer_t timer;
	struct sigevent event;
	struct itimerspec itimer;
};

/*----------OBJECT CONSTRUCTOR----------*/
extern Timer* TIMER_create(void){
	Timer* pointer = (Timer*)malloc(sizeof(Timer));
	if(pointer==NULL){ON_ERROR("TIMER_create");}
	return pointer;
}

/*----------OBJECT DESTRUCTOR----------*/
extern void TIMER_destroy(Timer* p){
	free(p);
}

/*----------OBJECT PUBLIC METHODS----------*/
extern void TIMER_init(Timer* p, int time_in_seconds){
	char * value = "value";
	p->event.sigev_notify = SIGEV_THREAD;
	p->event.sigev_value.sival_ptr = (void *)value;
	p->event.sigev_notify_function = TIMER_time_elapsed;
	p->event.sigev_notify_attributes = NULL;
	//Create timer
	if (timer_create(CLOCK_REALTIME, p->event, p->timer) != 0) {ON_ERROR("TIMER_start");}
	p->itimer.it_interval.tv_sec = 0;
	p->itimer.it_interval.tv_nsec = 0;
	p->itimer.it_value.tv_sec = time_in_seconds;
	p->itimer.it_value.tv_nsec = 0;
}

extern void TIMER_start(Timer* p){
	time(&current_time);
	fprintf(stdout, "lancement timer à : %s\n", ctime(&current_time));
	if (timer_settime(p->timer, 0, &itimer, NULL) != 0) {
		ON_ERROR("TIMER_start");
	}
}

/*----------PRIVATE FUNCTIONS----------*/

static void TIMER_time_elapsed(union sigval val){
	char * message = (char *)(val.sival_ptr);
	time(&current_time);
	fprintf(stdout, "message reçu : %s, à %s\n", message, ctime(&current_time));
}

static void ON_ERROR(char error[]){
	perror(error);
	exit(EXIT_FAILURE);
}
