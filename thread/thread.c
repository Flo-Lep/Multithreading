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
	pthread_mutex_t cond_mutex;
	pthread_cond_t cond;
	pthread_barrier_t barrier;
	sem_t * sem;
};

extern Thread* THREAD_create(void){
	Thread* pointer = (Thread*)malloc(sizeof(Thread));
	if(pointer==NULL){ON_ERROR("THREAD_create");}
	return pointer;
}

extern void THREAD_destroy(Thread* p){
	free(p);
}

/*----------OBJECT PUBLIC METHODS----------*/
extern void THREAD_init(Thread *p){
	pthread_attr_init(&(p->attr));
	pthread_attr_setdetachstate(&(p->attr), PTHREAD_CREATE_DETACHED);
	//pthread_attr_destroy(&attr); To be called afterwards
	//MUTEX
	//p->cond_mutex = PTHREAD_MUTEX_INITIALIZER;
	//p->cond = PTHREAD_COND_INITIALIZER;
}

extern void THREAD_init_barrier(Thread *p, int nb_of_barriers){
	pthread_barrier_init(&(p->barrier), NULL, nb_of_barriers);
}

extern void THREAD_init_semaphore(Thread *p){
	p->sem = sem_open("SEM", O_RDWR | O_CREAT, 0666, 1);
	if (p->sem == SEM_FAILED) {
			ON_ERROR("SEMAPHORE");
	}
}

extern void THREAD_start(Thread* p){
	if (pthread_create(&(p->thread), NULL, THREAD_demo_callback, NULL) != 0) {
		ON_ERROR("THREAD_start");
	}
}

extern void THREAD_detach(Thread *p){
	pthread_join(p->thread, NULL);
}

extern void THREAD_join(Thread *p){
	pthread_detach(p->thread);
}

extern void THREAD_exit(void){
	pthread_exit(EXIT_SUCCESS);
}

extern void * THREAD_demo_callback(void * arg){
	fprintf(stdout, "New thread started\n");
	return NULL;
}

extern void THREAD_mutex(Thread *p){
	pthread_mutex_lock(&(p->cond_mutex));
	pthread_cond_wait(&(p->cond), &(p->cond_mutex));
	pthread_mutex_unlock(&(p->cond_mutex));

	pthread_mutex_destroy(&(p->cond_mutex));
	pthread_cond_destroy(&(p->cond));
}

extern void THREAD_barrier(Thread *p){
	pthread_barrier_wait(&(p->barrier));
	//pthread_barrier_destroy(&barrier);
}

extern void THREAD_semaphore(Thread *p){
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
