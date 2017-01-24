#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"teatro.h"
int main(){
	key_t key=ftok(PATH,CHAR);
	key_t key2=ftok(PATH2,CHAR2);
	pid_t pid;
	int stat;
	int nclient=50,nvis=1;
	int nproc=nclient+nvis;
	int idsem,idshm;
	posto * p;

	/*CREAZIONE SHARED MEMORY*/
	idshm=shmget(key,sizeof(posto)*80,IPC_CREAT|0664);
	p=(posto*)shmat(idshm,0,0);
	/*inizializzazione struttura*/
	disponibilita=POSTI_DISP;
	for(int i=0;i<POSTI_DISP;i++){
		p[i].stato=libero;
		p[i].idCliente=0;	
	}
	/*CREAZIONE SEMAFORI*/
	idsem=semget(key2,2,IPC_CREAT|0664);
	semctl(idsem,mutex,SETVAL,1);
	semctl(idsem,cond_ok_pren,SETVAL,POSTI_DISP);
	/*GENERAZIONE PROCESSI*/
	for(int i=0;i<nproc;i++){
	pid=fork();
		if(pid==0){
			if(i==0){//processo visualizzatore
				execl("./visualizzatore","./visualizzatore",NULL);	
			}
			else{//processi clienti
				printf("[%d]Sono il processo cliente",getpid());
				sleep(rand()%5);
				for(int i=0;i<(rand()%4)+1;i++)
					prenotazione(p);
			}
			_exit(0);
		}	
	}
	/*TERMINAZIONE PROCESSI*/
	for(int i=0;i<nproc;i++){
		pid=wait(&stat);
		if(pid==-1)
			perror("Errore terminazione processo");
		else
			printf("[%d]Sono terminato\n",pid);	
	}
	/*RIMOZIONE STRUTTURE*/
	shmctl(idshm,IPC_RMID,0);
	semctl(idsem,mutex,IPC_RMID);
	semctl(idsem,cond_ok_pren,IPC_RMID);
return 1;
}
