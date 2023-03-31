#include <stdlib.h>
#include <stdio.h>
//#include <mqueue.h>
#include "message_queue.h"


static void ON_ERROR(char error[]);

/*----------OBJECT ATTRIBUTES----------*/
struct MessageQueueAttributes{
	mqd_t instance;
	char name;
	int MQ_MSG_MAX; //48
	int MQ_MSG_SIZE; //10
	char MQ_MSG_QUIT; //"END"
	struct mq_attr attr;
};

/*----------OBJECT CONSTRUCTOR----------*/
extern MessageQueue* MESSAGE_QUEUE_create(void){
	MessageQueue* pointer = (MessageQueue*)malloc(sizeof(MessageQueue));
	if(pointer==NULL){ON_ERROR("MESSAGE_QUEUE_create");}
	return pointer;
}

/*----------OBJECT DESTRUCTOR----------*/
extern void MESSAGE_QUEUE_destroy(MessageQueue* p){
	free(p);
}

/*----------OBJECT PUBLIC METHODS----------*/

extern void MESSAGE_QUEUE_init(MessageQueue* p){
	p->attr.mq_maxmsg = p->MQ_MSG_MAX;
	p->attr.mq_msgsize = p->MQ_MSG_SIZE;
	if ((p->instance = mq_open(p->name, O_RDONLY | O_CREAT, 0644, &p->attr)) == -1) {
		ON_ERROR("mq_receive()");
	}
}

extern void MESSAGE_QUEUE_process_message(MessageQueue* p){
	char buffer[p->MQ_MSG_SIZE];
	if (mq_receive(p->instance, buffer, p->MQ_MSG_SIZE, NULL) == -1) {
		mq_close(p->instance);
		mq_unlink(p->name);
		ON_ERROR("mq_receive()");
	}
	fprintf(stdout, "> %s", buffer);
}

extern void MESSAGE_QUEUE_add_message(MessageQueue* p, char buffer){

}

extern void MESSAGE_QUEUE_close(MessageQueue* p){
	// fermeture de la file de message
	mq_close(p->instance);
	// destruction de la file de message
	mq_unlink(p->name);
	//check error ?
}


/*----------PRIVATE FUNCTIONS----------*/

static void ON_ERROR(char error[]){
	perror(error);
	exit(EXIT_FAILURE);
}

