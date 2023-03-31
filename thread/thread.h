#ifndef _THREAD_H_
#define _THREAD_H_

typedef struct ThreadAttributes Thread;

extern Thread* THREAD_create(void);
extern void THREAD_destroy(Thread* p);

extern void THREAD_init(Thread *p);
extern void THREAD_start(Thread* p);
extern void THREAD_detach(Thread *p);
extern void THREAD_join(Thread *p);
extern void THREAD_exit(void);
extern void * THREAD_demo_callback(void * arg);

extern void THREAD_mutex(Thread *p);
extern void THREAD_barrier(Thread *p);
extern void THREAD_semaphore(Thread *p);

#endif /*_THREAD_H_*/
