#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<sys/shm.h>
#include"teatro.h"
/*WAIT & SIGNAL*/
void cond_wait(int numsem,int n){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-n;
	semop(numsem,&sem_buf,1);
}
void cond_signal(int numsem,int n){
	struct sembuf sem_buf;
	sem_buf.sem_num=numsem;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=n;
	semop(numsem,&sem_buf,1);
}
void prenotazione(posto*p){
	int i=0;
	cond_wait(mutex,1);
	/*il client stabilisce se c’è spazio*/
	if(disponibilita<POSTI_DISP){
		/* altrimenti termina subito con un messaggio di “disponibilità esaurita”*/
		cond_signal(mutex,1);
		printf("Disponiblita' esaurita!\n");
		exit(0);
	}
	while((i<POSTI_DISP)&&(p[i].stato!=libero))
		i++;
	/*. Se c’è disponiblità, pone in aggiornamento i primi posti liberi che trova, li occupa*/
	p[i].idCliente=getpid();
	p[i].stato=in_aggiornamento;
	/*decrementa la disponibilita*/
	disponibilita--;
	cond_signal(mutex,1);
	sleep(1);
	p[i].stato=occupato;
}
void bacheca(posto*p){
/*Il processo visualizzatore stampa a video, scrivendo su ogni riga il numero di posto, lo stato, ed eventualmente il cliente che ha occupato il posto.*/
	cond_wait(mutex,1);
	printf("\n----------------------------------------------------------\n");
	for(int i=0;i<POSTI_DISP;i++){
		if(p[i].stato==occupato)
			printf("[VISUALIZZATORE] posto: %d | stato: occupato | prenotato da: %d \n",i,p[i].idCliente);
		else if(p[i].stato==libero)
			printf("[VISUALIZZATORE] posto: %d | stato: libero | prenotato da: -  \n",i);
		
	}
	printf("\n----------------------------------------------------------\n");
	cond_signal(mutex,1);
}
