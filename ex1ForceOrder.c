#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* show(void* x);

int thread_count;

int main()
{
	pthread_t id = 0;
	thread_count = 0;
	int N;
	printf("Enter the number of threads you want to create: ");
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		printf("Thread number %d created.\n", i+1);
		pthread_create(&id,NULL,show,&thread_count);
		pthread_join(id,NULL);  //we add this to make the main thread wait for the thread with the id "id".
		// this way we maintain the order: thread creation, thread execution, exit thread, create the next thread ...
		id++;
	}
	return 0;
}

void* show(void* x)
{
	printf("\tHeey! I am thread number %d!\n",++thread_count);
}