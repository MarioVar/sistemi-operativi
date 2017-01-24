#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"header.h"
int main(){
	key1=ftok(path1,char1);
	key2=ftok(path2,char2);
	pid_t pid;
	int stat;
	coda_richiesta=msgget(key1,IPC_CREAT|0664);
	coda_risposta=msgget(key2,IPC_CREAT|0664);
	//printf("Sono l'eseguibile server\n");
	server();
	return 1;
}
