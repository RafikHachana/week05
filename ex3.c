#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<stdbool.h>

#define BUFFER_SIZE 10

int items;
bool sleeping_consumer,sleeping_producer;


void* consumer(void* in)
{
	sleeping_consumer = false;
	while(true)
	{
		if(items==0) sleeping_consumer = true;
		if(sleeping_consumer) continue;
		items--;
		printf("I am the consumer!! And there are %d items in the buffer\n",items);
		if(items==BUFFER_SIZE-1) sleeping_producer = false;
	}
}

void* producer(void* in)
{
	sleeping_producer = false;
	while(true)
	{
		if(items==BUFFER_SIZE) sleeping_producer = true;
		if(sleeping_producer) continue;
		items++;
		printf("I am the producer!! And there are %d items in the buffer\n",items);
		if(items==1) sleeping_consumer = false;
	}
}

int main()
{
	pthread_t consumer_thread,producer_thread;
	items = 0;
	pthread_create(&producer_thread,NULL,producer,NULL);
	pthread_create(&consumer_thread,NULL,consumer,NULL);
	pthread_join(producer_thread,NULL);
	pthread_join(consumer_thread,NULL);


/*

		A race condition happens with the variable "items"
		the consumer thread reads the value of items(which is 0) and is then is stopped by the scheduler
		the producer then produces items, increments items (and since items>0 itsends a wakeup call to the consumer)
		since the consumer thread is not sleeping (just stopped by the scheduler) the wakeup call is lost
		the consumer thread is then running again, but it puts itself to sleep because the last value of items it was reading is 0
		producer fills the buffer and then goes to sleep

		and we end up with both threads sleeping forever
*/


	return 0;
}