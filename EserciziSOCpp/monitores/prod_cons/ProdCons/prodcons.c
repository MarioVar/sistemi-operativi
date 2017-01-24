#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"../monitor/monitor.h"
#include"prodcons.h"

int main(){
//INIZIALIZZAZIONE VARIABILI
pid_t pid;
key_t key_shm=ftok(".",'a');
int numeroproduttori=8,numeroconsumatori=4;
int numeroprocessi=numeroproduttori+numeroconsumatori;
buffer* b;
Monitor m;
int idshm,stat;
//CREAZIONE SHARED MEMORY
idshm=shmget(key_shm,4*sizeof(int),IPC_CREAT|0664);
b=(buffer*)shmat(idshm,0,0);
initBuffer(b);
//INIZIALIZZAZIONE MONITOR
init_monitor (&m,N_CONDS);

//GENERAZIONE PROCESSI
for(int i=0;i<numeroprocessi;i++){
	pid=fork();
	if(pid<0){
		perror("Errore fork");
		return -1;
		}
	else if(pid==0){
		if((i%2)==0){
			sleep(1);
			printf("<%d> Sono il figlio produttore\n",getpid());
			produzione(&m,b);		
		}
		else{
			printf("<%d> Sono il figlio consumatore\n",getpid());	
			consumo(&m,b);	
		}
		exit(0);
	}
	
}
//TERMINAZIONE PROCESSI
for(int i=0;i<numeroprocessi;i++){
	pid=wait(&stat);
	if(pid==-1){
		printf("errore terminazione processo con pid:%d\n",getpid());
		return -2;
	}
	else	
		printf("<%d> Processo terminato con status %d\n",getpid(),pid);	
}
//DEALLOCAZIONE STRUTTURE
leave_monitor(&m);
shmctl(idshm,IPC_RMID,0);
return 0;
}
