#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* show(void* x);

//int thread_count;

int main()
{
	int thread_count = 0;
	int N;
	printf("Enter the number of threads you want to create: ");
	scanf("%d",&N);
	pthread_t id[N]	;
	for(int i=0;i<N;i++)
	{
		printf("Thread number %d created.\n", i+1);
		pthread_create(&id[i],NULL,show,&thread_count);
		thread_count++;
	}
	for(int i=0;i<N;i++)
	{
		pthread_join(id[i],NULL); //join to main thread so that all threads finish their work
	} 
	return 0;
}

void* show(void* x)
{
	int current_number = * ((int*) x);
	printf("\tHeey! I am thread number %d!\n",current_number);
}