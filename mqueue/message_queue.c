/*
 * message_queue.c
 * Created on: April 2, 2023
 * Author: Florentin LEPELTIER
 */

#include <stdlib.h>
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "message_queue.h"

//WARNING : THE MESSAGE QUEUE NAME MUST BEGIN WITH A SLASH : /xxxx

static void ON_ERROR(char error[]);

/*----------OBJECT ATTRIBUTES----------*/
struct MessageQueueAttributes{
	mqd_t instance;
	char name[5];
	int MQ_MSG_MAX; //10
	int MQ_MSG_SIZE; //48
	struct mq_attr attr;
};

/*----------OBJECT CONSTRUCTOR----------*/
MessageQueue* MESSAGE_QUEUE_create(char name[]){
	MessageQueue* pointer = (MessageQueue*)malloc(sizeof(MessageQueue));
	if(pointer==NULL){ON_ERROR("MESSAGE_QUEUE_create");}
	for(int i=0;i<sizeof(&name);i++){
		strcpy(&(pointer->name)[i], &(name)[i]);
	}
	return pointer;
}

/*----------OBJECT DESTRUCTOR----------*/
void MESSAGE_QUEUE_destroy(MessageQueue* p){
	free(p);
}

/*----------OBJECT PUBLIC METHODS----------*/

void MESSAGE_QUEUE_init(MessageQueue* p){
	p->MQ_MSG_MAX = MSG_MAX;
	p->MQ_MSG_SIZE = MSG_SIZE;
	p->attr.mq_maxmsg = MSG_MAX;
	p->attr.mq_msgsize = MSG_SIZE;
	if ((p->instance = mq_open(p->name, O_RDWR | O_CREAT | O_EXCL, 0644, &(p->attr))) == -1) {
		mq_unlink(p->name);
		p->instance = mq_open(p->name, O_RDWR | O_CREAT | O_EXCL, 0644, &(p->attr));
	}
	if(mq_getattr(p->instance, &(p->attr))==-1){
		mq_close(p->instance);
		ON_ERROR("MQ_init()");
	}
}

void MESSAGE_QUEUE_process_message(MessageQueue* p){
	char buffer[p->MQ_MSG_SIZE];
	if (mq_receive(p->instance, buffer, p->MQ_MSG_SIZE, NULL) == -1) {
		mq_close(p->instance);
		mq_unlink(p->name);
		ON_ERROR("MQ_process_message()");
	}
	fprintf(stdout, "> %s", buffer);
}

void MESSAGE_QUEUE_add_message(MessageQueue* p, char buffer[]){
	if(mq_send(p->instance, buffer, p->MQ_MSG_SIZE, 0) == -1){
		mq_close(p->instance);
		ON_ERROR("MQ_add_message");
	}
}

void MESSAGE_QUEUE_close(MessageQueue* p){
	mq_close(p->instance);
	mq_unlink(p->name);
	//check error ?
}


/*----------PRIVATE FUNCTIONS----------*/

static void ON_ERROR(char error[]){
	perror(error);
	exit(EXIT_FAILURE);
}

