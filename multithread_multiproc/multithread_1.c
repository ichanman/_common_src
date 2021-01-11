#include <stdio.h>
#include "util.h"

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
#define MAX_THREAD 10

int rep;
/**
 * \brief sub thread that will run parallel with main
 */
void * subthread(void * arg)
{
	int i = 0;
	char * mstr = (void *)arg;
	for(i=0;i<rep;i++){
		pthread_mutex_lock(&mutex);
		display(mstr);
		pthread_mutex_unlock(&mutex);
	}
	return EXIT_SUCCESS;
}
/**
 * \brief mutex initialization
 */
void mutex_init()
{
	if(pthread_mutex_init(&mutex,NULL) != 0){
		perror("mutex init: ");
		exit(EXIT_FAILURE);
	}
}
/**
 * \brief the main program
 */
int main(int argc, char *argv[])
{
	if(argc < 3)
		exit(EXIT_FAILURE);
	int i,num_of_str;
	num_of_str = argc - 2;
	rep = atoi(argv[1]);
	mutex_init();
	pthread_t thread[MAX_THREAD];
	for(i=0;i<num_of_str;i++)
	{
		pthread_create(&thread[i], NULL,(void*) subthread, (void*)argv[i+2]);
	}
	for(i=0;i<num_of_str;i++)
	{
		pthread_join(thread[i],NULL);
	}

	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
