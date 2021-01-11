#include <stdio.h>
#include "util.h"

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int rep;
int count_init;
int num_of_str = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;
#define MAX_THREAD 10

/**
 * \brief sub thread that will run parallel with main
 */
void * subthread(void * arg)
{
	char * mstr = (void *)arg;
	pthread_mutex_lock(&mutex);
	init();
	count_init++;
	while(count_init < num_of_str)
	{
		pthread_cond_wait(&cond,&mutex);
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	int i;
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
void cond_init()
{
	if(pthread_cond_init(&cond,NULL) != 0){
		perror("condition variable init: ");
		exit(EXIT_FAILURE);
	}
}
/**
 * \brief the main program
 */
int main(int argc, char *argv[])
{
	int i;
	count_init = 0;
	num_of_str = argc - 2;
	rep = atoi(argv[1]);
	mutex_init();
	cond_init();
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
	pthread_cond_destroy(&cond);
	pthread_exit(NULL);
}
