#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#define MAXPROCESS 10
int sem_id;



void semaphore_init()
{
    int semflg = (666 | IPC_CREAT);
    int n_sem  = 1;
    sem_id = semget(IPC_PRIVATE,n_sem,semflg);
    if(sem_id == -1)
        perror("sem_get():");
    semctl(sem_id,0,SETVAL,1);
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
	struct sembuf sb;
    int n_sops = 1;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	semaphore_init();
	pid_t pid[MAXPROCESS];
	pid_t wpid;
	int i,j;
	for(i=0;i<num_of_str;i++)
	{
		pid[i] = fork();
		if (pid[i] == 0) { /* Child */
			for(j=0;j<rep;j++){
                /** wait**/
                sb.sem_op = -1;
                semop(sem_id,&sb,n_sops);
                /*****/
                display(argv[i+2]);
                /** pos **/
                sb.sem_op = 1;
                semop(sem_id,&sb,n_sops);
				/*****/
			}
			exit(0);
		}
	}
	while ((wpid = wait(NULL)) > 0);
	do_cleanup();
	return 0;
}
