#include <stdio.h>
#include <unistd.h>
#include "timer.h"

int main(){
	int nb_of_seconds = 5;
	fprintf(stdout, "*****Starting timer prog*****\n");
	Timer* timer = TIMER_create();
	fprintf(stdout, "TIMER created\n");
	TIMER_init(timer, nb_of_seconds);
	fprintf(stdout, "TIMER initialised\n");
	TIMER_start(timer);
	fprintf(stdout, "main still running for 10 seconds\n\n");
	for(int i=0;i<10;i++){
		sleep(1);
	}
	TIMER_destroy(timer);
	fprintf(stdout, "TIMER destroyed\n");
	fprintf(stdout, "*****Ending timer prog*****\n");
	return 0;
}
