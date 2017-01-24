#include"header.h"
int main(){
	int idshm2,idsem;
	key2=ftok(path1,char1);
	key3=ftok(path3,char3);
	idshm2=shmget(key2,sizeof(Gestore),IPC_CREAT|0664);
	Gestore* g=(Gestore*)shmat(idshm2,0,0);
	idsem=semget(key3,3,IPC_CREAT|0664);
	while(!g->stop){
		elabora(g,idsem);
		sleep(1);	
	}
return 0;
}
