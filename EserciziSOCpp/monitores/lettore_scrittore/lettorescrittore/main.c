#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


#include"../monitor/monitor.h"
#include"ls.h"
int main(){
	int stat;
	key_t key_shm=IPC_PRIVATE;
	int idshm;
	memory* mem;
	Monitor M;
	int numprod=5,numlett=5;
	int numeroprocessi=numprod+numlett;
	pid_t pid;

	/* creo e inizializzo la shared memory*/
	idshm=shmget(key_shm,sizeof(memory),IPC_CREAT|0664);
	mem=(memory*)shmat(idshm,0,0);
	mem->occupato=0;
	mem->numlettori=0;
	mem->messaggio=0;

	/*inizializzo monitor*/
	init_monitor (&M,NUM_CONDITIONS);

	/*generazione processi*/
	for(int i=0;i<numeroprocessi;i++){
		pid=fork();
		if(pid==0){
			if(i%2==0){
				sleep(1);
				printf("[%d] Sono il figlio lettore\n",getpid());
				Lettura(mem,&M);
			}
			else{
				printf("[%d] Sono il figlio produttore\n",getpid());
				Produzione(mem,&M);			
			}
		exit(0);		
		}
	}
	/*Aspetto la terminazione di tutti i processi*/
	for(int i=0;i<numeroprocessi;i++){
		pid=wait(&stat);
		if(pid==-1){
			perror("errore di trminazione processo \n");		
		}
		else
			printf("Figlio %d e' morto con status=%d\n",pid,stat);	
	}
	
	/*rimozione shared memory*/
    	 shmctl(idshm,IPC_RMID,0);

	/*Rimozione monitor*/
	remove_monitor(&M);
return 0;
}
