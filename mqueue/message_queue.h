/*
 * message_queue.h
 * Created on: April 2, 2023
 * Author: Florentin LEPELTIER
 */

#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#define MSG_MAX		(10)
#define MSG_SIZE	(48)
//#define MQ_NAME 	"MQ_NAME"

typedef struct MessageQueueAttributes MessageQueue;

/*CONSTRUCTOR*/
extern MessageQueue* MESSAGE_QUEUE_create(char name[]);

/*DESTRUCTOR*/
extern void MESSAGE_QUEUE_destroy(MessageQueue* p);

/*METHODS*/
extern void MESSAGE_QUEUE_init(MessageQueue* p);
extern void MESSAGE_QUEUE_add_message(MessageQueue* p, char buffer[]);
extern void MESSAGE_QUEUE_process_message(MessageQueue* p);
extern void MESSAGE_QUEUE_close(MessageQueue* p);

#endif /*_MESSAGE_QUEUE_H_*/
