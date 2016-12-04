#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include"../monitor/monitor.h"
#include"magazzino.h"
int main(){
	int i=0;
	Monitor mo;
	int stat;
	pid_t pid;
	scaffale* m;
	int id_shm=shmget(IPC_PRIVATE,sizeof(scaffale)*100,IPC_CREAT|0664);
	if(id_shm<0)
		perror("Errore creazione shared memory");
	m=(scaffale*)shmat(id_shm,0,0);
	init_monitor(&mo,2);
	//inizializzazione struttura
	livello_scorte=0;
	
	while(i<N){
		m[i].id_fornitore=0;
		m[i].stato=libero;
#ifdef DEBG
		printf("m[i]->id_fornitore=%u,m[i]->stato=%u, --[%d]\n",m[i]->id_fornitore,m[i]->stato,i);
#endif
		i++;
	}	
	
	
	for(int i=0;i<numproc;i++){
		pid=fork();
		if(pid==0){
			if(i%2){//processo fornitore
				for(int i=0;i<15;i++){
				printf("[%d]Sono il processo fornitore\n",getpid());
				sleep(1);
				fornitura(&mo,m);				
				}	
							
			}
			else{//processo cliente	
				for(int i=0;i<15;i++){
				printf("[%d]Sono il processo cliente\n",getpid());
				sleep(1);
				acquisto(&mo,m);
				}
			}
			exit(0);
		}
	}
	for(int i=0;i<numproc;i++){
		pid=wait(&stat);
		if(pid==-1)
			perror("errore");
		else
			printf("Il processo %d e' terminato con status %d\n",pid,stat);
	}
	shmctl(id_shm,IPC_RMID,0);
	remove_monitor(&mo);

		
}
