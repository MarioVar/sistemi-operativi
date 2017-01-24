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
	int shm,sem;
	key_t idsem,idshm;
	//idsem=12344452;
	//id shm condivisa
	idshm=ftok(PATH_SHM,CHAR_SHM);
	//id semaforo condiviso
	idsem=ftok(PATH_SEM,CHAR_SEM);
	bufferCircolare* b;
	
	shm = shmget(idshm,0,IPC_CREAT | 0664);
	sem = semget(idsem,0,IPC_CREAT | 0664);
	printf("[Consumatore] Sono il processo consumatore con pid %d,shmid = %d,semid = %d\n",getpid(),shm,sem);
	b = (bufferCircolare*) shmat(shm,0,0);

	for(int i=0;i<2;i++){
		consumaElementi(sem,b);
	}
	return 1;
}

