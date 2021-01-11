#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>
#define MAXPROCESS 10
int sem_id;

void semaphore_init()
{
    int semflg = (666 | IPC_CREAT);
    int n_sem  = 3;
    sem_id = semget(IPC_PRIVATE,n_sem,semflg);
    if(sem_id == -1)
    {
        perror("sem_get():");
        exit(1);
    }
    semctl(sem_id,0,SETVAL,1);
    semctl(sem_id,1,SETVAL,0);
    semctl(sem_id,2,SETVAL,0);
}
void do_cleanup()
{
	if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("cleanup semctl");
        exit(1);
    }
}
int main(int argc, char *argv[])
{
	int rep, num_of_str;
	num_of_str = argc - 2;
	rep = atoi(argv[1]);
	int n_sops = 1;
	struct sembuf sem_sig  = {0,1,SEM_UNDO};
    struct sembuf sem_wait = {0,-1,SEM_UNDO};
	semaphore_init();
	pid_t pid[MAXPROCESS];
	pid_t wpid;
	int i,j;
    int count_init = 0;
	for(i=0;i<num_of_str;i++)
	{
		pid[i] = fork();
		if (pid[i] == 0) { /* Child */
            sem_wait.sem_num = 0;
            semop(sem_id,&sem_wait,n_sops);
            init();
            sem_sig.sem_num = 0;
            semop(sem_id,&sem_sig,n_sops);
            sem_sig.sem_num = 1;
            semop(sem_id,&sem_sig,n_sops);

			for(j=0;j<rep;j++){
                /** wait**/
                sem_wait.sem_num = 2;
                semop(sem_id,&sem_wait,n_sops);
                /*****/
                //printf("[%i,%li] %d\n", getpid(), pthread_self(),i);
                display(argv[i+2]);
                /** pos **/
                sem_sig.sem_num = 2;
                semop(sem_id,&sem_sig,n_sops);
				/*****/
			}
			exit(0);
		}else{
            sem_wait.sem_num = 1;
            semop(sem_id,&sem_wait,n_sops);
            count_init++;
            if(count_init==(num_of_str))
            {
                sem_sig.sem_num = 2;
                semop(sem_id,&sem_sig,n_sops);
            }

		}
	}
	while ((wpid = wait(NULL)) > 0);
	do_cleanup();
	return 0;
}
