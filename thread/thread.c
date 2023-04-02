/*
 * thread.c
 * Created on: April 2, 2023
 * Author: Florentin LEPELTIER
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>

#include "thread.h"

static void ON_ERROR(char error[]);

/*----------OBJECT ATTRIBUTES----------*/
struct ThreadAttributes{
	pthread_t thread;
	pthread_attr_t attr;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_barrier_t barrier;
	sem_t * sem;
};

Thread* THREAD_create(void){
	Thread* pointer = (Thread*)malloc(sizeof(Thread));
	if(pointer==NULL){ON_ERROR("THREAD_create");}
	return pointer;
}

void THREAD_destroy(Thread* p){
	pthread_attr_destroy(&(p->attr));
	free(p);
}

/*----------OBJECT PUBLIC METHODS----------*/
void THREAD_init(Thread *p){
	pthread_attr_init(&(p->attr));
	pthread_attr_setdetachstate(&(p->attr), PTHREAD_CREATE_DETACHED);
}

void THREAD_start(Thread* p){
	if (pthread_create(&(p->thread), NULL, THREAD_demo_callback, NULL) != 0) {
		ON_ERROR("THREAD_start");
	}
}

void THREAD_detach(Thread *p){
	pthread_join(p->thread, NULL);
}

void THREAD_join(Thread *p){
	pthread_detach(p->thread);
}

void THREAD_exit(void){
	pthread_exit(EXIT_SUCCESS);
}

void * THREAD_demo_callback(void * arg){
	fprintf(stdout, "New thread started\n");
	return NULL;
}

/*******************TOOLS*************************/

void THREAD_init_mutex(Thread *p){
	p->mutex = PTHREAD_MUTEX_INITIALIZER;
	p->cond = PTHREAD_COND_INITIALIZER;
}

void THREAD_init_barrier(Thread *p, int nb_of_barriers){
	pthread_barrier_init(&(p->barrier), NULL, nb_of_barriers);
}

void THREAD_init_semaphore(Thread *p){
	p->sem = sem_open("SEM", O_RDWR | O_CREAT, 0666, 1);
	if (p->sem == SEM_FAILED) {
			ON_ERROR("SEMAPHORE");
	}
}

void THREAD_mutex(Thread *p){
	pthread_mutex_lock(&(p->mutex));
	pthread_cond_wait(&(p->cond), &(p->mutex));
	pthread_mutex_unlock(&(p->mutex));

	pthread_mutex_destroy(&(p->mutex));
	pthread_cond_destroy(&(p->cond));
}

void THREAD_barrier(Thread *p){
	pthread_barrier_wait(&(p->barrier));
	//pthread_barrier_destroy(&barrier);
}

void THREAD_semaphore(Thread *p){
	sem_wait(p->sem);
	sem_post(p->sem);
	if (sem_unlink("SEM") != 0) {
		ON_ERROR("SEM unlink");
	}
}

/*----------PRIVATE FUNCTIONS----------*/

static void ON_ERROR(char error[]){
	perror(error);
	exit(EXIT_FAILURE);
}
