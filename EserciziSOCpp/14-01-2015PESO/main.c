#include"header.h"
int main(){
	pid_t pid;
	int idshm,idshm2,stat;
	richiesta* r;
	Monitor m;
	idshm=shmget(IPC_PRIVATE,sizeof(richiesta)*N,IPC_CREAT|0664);
	idshm2=shmget(IPC_PRIVATE,sizeof(Gestione),IPC_CREAT|0664);
	r=(richiesta*)shmat(idshm,0,0);
	Gestione* g=(Gestione*)shmat(idshm2,0,0);
	for(int i=0;i<N;i++){
		r[i].pid=0;
		r[i].posizione=0;	
	}
	g->testa=0;
	g->coda=0;
	g->spazio_disp=N;
	g->msg_disp=0;
	g->posattuale;
	init_monitor(&m,3);
	for(int i=0;i<nProc;i++){
		pid=fork();
		if(pid==0){
			if(i==0){
				schedula(r,&m,g);
			}
			else{
				for(int k=0;k<5;k++)
					scrittura(r,&m,g);
			}
			exit(0);
		}
	}
	for(int i=0;i<nProc;i++){
		pid=wait(&stat);
		printf("[Main]Il processo %d è terminato\n",pid);	
	}
	remove_monitor(&m);
	shmctl(idshm,IPC_RMID,0);
	return 0;
}
