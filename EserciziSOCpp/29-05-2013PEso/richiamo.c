#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include"header.h"
int main(){
	key1=ftok(path1,char1);
	key2=ftok(path2,char2);
	pid_t pid;
	int stat;
	coda_richiesta=msgget(key1,IPC_CREAT|0664);
	coda_risposta=msgget(key2,IPC_CREAT|0664);
	for(int i=0;i<4;i++){
		pid=fork();
		if(pid==0){
			if(i==0){
				//execl("./server","./server",NULL);
				server();			
			}
			else{
				execl("./client","./client",NULL);
				client(0);			
			}
			exit(0);
		}	
	}
	for(int i=0;i<4;i++){
		pid=wait(&stat);
		if(pid==-1)
			perror("Errore terminazione");
		else
			printf("[%d] Sono terminato\n",pid);	
	}
	sleep(3);
	client(1);
	printf("[Master]Ho chiuso la connesione con il server\n");
	msgctl(coda_risposta,IPC_RMID,0);
	msgctl(coda_richiesta,IPC_RMID,0);

return 0;
}
