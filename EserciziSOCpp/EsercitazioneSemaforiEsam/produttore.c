#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "esercitazione.h"
int main(){
	int shmid,semid;
	srand(time(NULL));
	bufferCircolare* b;
	key_t key_shm,key_sem;
	key_shm = ftok(PATH_SHM,CHAR_SHM);
        key_sem = ftok(PATH_SEM,CHAR_SEM);
	//key_sem=12344452;

	shmid = shmget(key_shm,0,IPC_CREAT | 0664);
	semid = semget(key_sem,0,IPC_CREAT | 0664);

	printf("[PRODUTTORE] <%d> shmid = %d, semid = %d\n",getpid(),shmid,semid);
	b = (bufferCircolare*) shmat(shmid,0,0);
	produciElemento(semid,b);
	return 1;
}
