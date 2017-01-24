#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"teatro.h"
int main(){
	posto* p;
	key_t key=ftok(PATH,CHAR);
	key_t key2=ftok(PATH2,CHAR2);
	int idshm=shmget(key,sizeof(posto)*80,IPC_CREAT|0664);
	int idsem=semget(key2,2,IPC_CREAT|0664);
	p=(posto*)shmat(idshm,0,0);
	printf("[%d]Sono il processo visualizzatore",getpid());
	while(1){
		sleep(1);
		bacheca(p);
	}
	return 1;
}
