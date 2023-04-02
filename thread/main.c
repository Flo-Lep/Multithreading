/*
 * main.c
 * Created on: April 2, 2023
 * Author: Florentin LEPELTIER
 */

#include <stdio.h>
#include "thread.h"

int main(){
	fprintf(stdout, "*****Starting THREAD prog*****\n");
	Thread* new_thread = THREAD_create();
	fprintf(stdout, "THREAD created\n");
	THREAD_start(new_thread);
	THREAD_join(new_thread);
	THREAD_destroy(new_thread);
	fprintf(stdout, "THREAD destroyed\n");
	fprintf(stdout, "*****Ending THREAD prog*****\n");
	return 0;
}
