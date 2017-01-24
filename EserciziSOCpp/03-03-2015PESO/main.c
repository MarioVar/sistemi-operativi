#include"header.h"
int main(){
	int stat;
	pid_t pid;
	int idshm2,idsem;
	key1=ftok(path0,char0);
	key2=ftok(path1,char1);
	key3=ftok(path3,char3);
	idshm2=shmget(key2,sizeof(Gestore),IPC_CREAT|0664);
	Gestore* g=(Gestore*)shmat(idshm2,0,0);
	idsem=semget(key2,3,IPC_CREAT|0664);
	semctl(idsem,mutex,SETVAL,1);
	semctl(idsem,ok_lettura,SETVAL,0);
	semctl(idsem,ok_scrittura,SETVAL,0);
	inizializza(g);
	for(int i=0;i<4;i++){
		pid=fork();
		if(pid==0){
			if(i==0)
				execlp("./P1","./P1",NULL);
			else if(i==1)
				execlp("./P2","./P2",NULL);
			else
				execlp("./P3","./P3",NULL);
			
		exit(0);
		}	
	}
	sleep(15);
	g->stop=1;
	for(int i=0;i<4;i++){
		pid=wait(&stat);
		printf("Il processo con pid=<%d> è terminato",pid);	
	}
	shmctl(idshm2,IPC_RMID,0);
	shmctl(idsem,0,IPC_RMID);
return 0;
}
