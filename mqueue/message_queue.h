#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

typedef struct MessageQueueAttributes MessageQueue;

/*CONSTRUCTOR*/
extern MessageQueue* MESSAGE_QUEUE_create(void);

/*DESTRUCTOR*/
extern void MESSAGE_QUEUE_destroy(MessageQueue* p);

/*METHODS*/
extern void MESSAGE_QUEUE_init(MessageQueue* p);
extern void MESSAGE_QUEUE_add_message(MessageQueue* p, char buffer);
extern void MESSAGE_QUEUE_process_message(MessageQueue* p);
extern void MESSAGE_QUEUE_close(MessageQueue* p);

#endif /*_MESSAGE_QUEUE_H_*/
