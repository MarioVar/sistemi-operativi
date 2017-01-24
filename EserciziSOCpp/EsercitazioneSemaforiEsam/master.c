#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include"esercitazione.h"
#include <sys/types.h>
int main(){
	
	int shmid,semid;
	
	key_t key_shm,key_sem;
	key_shm = ftok(PATH_SHM,CHAR_SHM);
	key_sem = ftok(PATH_SEM,CHAR_SEM);
	//key_sem=12344452;
	int numeroProduttori=10,numeroConsumatori=1;
	int numprocessi=numeroProduttori+numeroConsumatori;
	bufferCircolare* buf;
	int stat;
	pid_t pid;
	
	//creazione shared memory
	shmid =shmget(key_shm,sizeof(bufferCircolare),IPC_CREAT | 0664);
	//creazione semafori
	semid =semget(key_sem,2,IPC_CREAT |0664);
	//attach shm
	buf= (bufferCircolare*)shmat(shmid,0,0);
	printf("[MASTER] - Shmid : %d, Semid: %d\n",shmid,semid);
	//inizializzazione semafori
	semctl(semid,MUTEX,SETVAL,1);
	semctl(semid,SINC,SETVAL,N+1);
	
	
	//GENERAZIONE PRODUTTORI E DEL CONSUMATORE
	srand(time(NULL));
	for(int i=0;i<numprocessi;i++){
		pid=fork();
		if(pid==0){	
			if(i==0){//processo consumatore
				execl("./consumatore","./consumatore",NULL);
			}
			else{//processi produttori
				execl("./produttore","./consumatore",NULL);
			}
			_exit(0);
		}
		sleep(1+rand()%3);
	}
	//controllo processi defunti e rimozione strutture istanziate
	for(int i=0;i<numprocessi;i++){
		pid=wait(&stat);
		if (pid==-1)
			perror("errore");
		else
		 	printf ("Figlio n.ro %d e\' \n ",pid);	
	}

	shmctl(shmid,IPC_RMID,0);
	semctl(semid,0,IPC_RMID);
	
	return 0;
}
