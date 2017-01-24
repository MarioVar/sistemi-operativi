#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include"clientServer.h"
int main(){
	key_t key=ftok(".",'a');
	pid_t pid;
	int nClient=3,nServer=1,nProc=nClient+nServer;
	int stat,i;
	idcoda1=msgget(IPC_PRIVATE,IPC_CREAT|0664);
	idcoda2=msgget(key,IPC_CREAT|0664);
	pid=fork();
	if(pid==0){
		//processo server
		server();
		_exit(0);
	}
    //creo processi utenti
    for(i=0;i<nClient;i++){
        pid=fork();
        if(pid==0){
	    printf("[%d]Sono il client %d\n",getpid(),i);
            client(0);
            _exit(0);
        }   
    }   
 
 
    //padre in attesa
    for(i=0;i<nClient;i++){
        pid=wait(0);
	printf("[MAIN]Il client con pid:%d è terminato\n",pid);
     
    }
	client(1);
	printf("[PADRE-TERMINATOR] Invio richiesta chiusura connessione al server...\n");
	pid=wait(0);
	msgctl(idcoda1,IPC_RMID,0);
	msgctl(idcoda2,IPC_RMID,0);
return 0;
}
