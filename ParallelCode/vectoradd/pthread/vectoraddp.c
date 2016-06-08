#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct message{
	char* msg;
	int msg_num;
}message_t;

void* print_message_function(void* ptr){
	message_t* msg= (message_t*)ptr;
	printf("%s: %d\n",msg->msg,msg->msg_num);
}

int main(int argc, char** argv){

	pthread_t thread1, thread2;
	message_t msg1 = {"Thread 1",1};
	message_t msg2 = {"Thread 2",2};

	int result = pthread_create(&thread1, NULL, print_message_function, (void*) &msg1);
	if( result ){
		fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
		exit(EXIT_FAILURE);
	}
	pthread_join(thread1, NULL);

	return 0;
}
