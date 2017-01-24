#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include <sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"header.h"
int main(){
	pid_t pid;
	key_t key=ftok(".",'a');
	key_t key2=ftok(".",'b');
	int idcoda,idcoda2,stat;
	int nclient=5,nserver=1,nprinter=1;
	int nproc=nclient+nserver+nprinter;
	idcoda=msgget(key,IPC_CREAT|0664);
	idcoda2=msgget(key2,IPC_CREAT|0664);
	/*GENERAZIONE PROCESSI*/
	for(int i=0;i<nproc;i++){
	pid=fork();
		if(pid==0){
		/*PRINER*/
				if(i==0){
					printf("Sono il processo printer [con pid %d]\n",getpid());
					printer(idcoda2);
				}		
		
		/*SERVER*/
				if(i==1){
					printf("Sono il processo server [con pid %d]\n",getpid());
					server(idcoda,idcoda2);
				}
		/*CLIENT*/
				if(i>1){
					for(int i=0;i<15;i++){
						printf("Sono il processo client [con pid %d]\n",getpid			());						client(idcoda);						
						sleep(1);
					}
				}
		
				_exit(0);
		}
	}
	/*TERMINAZIONE PROCESSI E DEALLOCAZIONE CODA MESSAGGI*/
	for(int i=0;i<nproc;i++){
		pid=wait(&stat);
		if(pid==-1)
			perror("Errore terminazione processo");
		else
			printf("il processo <%d> e' terminato",pid);	
	}
	msgctl(idcoda,IPC_RMID,0);
	msgctl(idcoda2,IPC_RMID,0);
return 0;
}
