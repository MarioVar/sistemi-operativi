#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/wait.h>
#include"mex.h"
int main(){
	int nprocessi=nclient+nserver+nbalanc;
	int stat;
	pid_t pid;
	codaClient=msgget(IPC_PRIVATE,IPC_CREAT);
	codaBalancer=msgget(IPC_PRIVATE,IPC_CREAT);
	for(int i=0;i<nprocessi;i++){
		pid=fork();
		if(pid==0){
			if(i<nclient){//processi client
				/*execv("./client",0);*/
				for(int k=0;k<15;k++){
				sleep(1);
				printf("[%d]Sono il processo client %d\n",getpid(),i);
				richiestaC();
				}	
			}
			else if(i==nprocessi){//processo balancer
				for(int i=0;i<nclient;i++)
					inoltroB();
			}
			else{//processo server
				Server();
			}
			_exit(0);
		}	
	}
	for(int i=0;i<nprocessi;i++){
		pid=wait(&stat);
		if(pid==-1)
			perror("errore terminazione processi");
		else
			printf("Il processo %d è terminato \n",pid);	
	}
	msgctl(codaBalancer,IPC_RMID,0);
	msgctl(codaClient,IPC_RMID,0);
	return 1;
}
