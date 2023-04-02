#include <stdio.h>
#include "message_queue.h"

//WARNING : THE MESSAGE QUEUE NAME MUST BEGIN WITH A SLASH : /xxxx

int main(){
	fprintf(stdout, "*****Starting MESSAGE_QUEUE prog*****\n");
	char mq_name[] = "/mq_name";
	MessageQueue* mq = MESSAGE_QUEUE_create(mq_name);
	fprintf(stdout, "MESSAGE_QUEUE created\n");
	MESSAGE_QUEUE_init(mq);
	fprintf(stdout, "MESSAGE_QUEUE initialised\n");
	MESSAGE_QUEUE_add_message(mq, "new message inserted from main\n");
	fprintf(stdout, "Message added to MESSAGE_QUEUE\n");
	MESSAGE_QUEUE_process_message(mq);
	fprintf(stdout, "Message received by MESSAGE_QUEUE\n");
	MESSAGE_QUEUE_destroy(mq);
	fprintf(stdout, "MESSAGE_QUEUE destroyed\n");
	fprintf(stdout, "*****Ending MESSAGE_QUEUE prog*****\n");
	return 0;
}
