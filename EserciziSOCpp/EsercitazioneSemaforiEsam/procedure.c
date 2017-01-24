#include<math.h>
#include"esercitazione.h" 
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



void WaitZ(int id,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=id;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=0;
	semop(id,&sem_buf,1);
}
void Wait(int id,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=id;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=-1;
	semop(id,&sem_buf,1);
}
void Signal(int id,int numsem){
	struct sembuf sem_buf;
	sem_buf.sem_num=id;
	sem_buf.sem_flg=0;
	sem_buf.sem_op=1;
	semop(id,&sem_buf,1);
}
int leggi_valore(int id_sem,int semaforo){
	return semctl(id_sem,semaforo,GETVAL);
}

void produciElemento(int semid,bufferCircolare* b){	
		
	Wait(semid,MUTEX);
	//codice produzione
	b->elementi[b->testa]=(1+rand()%10);
	printf("[Produttore %d] ho prodotto %d in posizione %d\n",getpid(),b->elementi[b->testa],b->testa);
	b->testa = ++(b->testa) % N;
	Wait(semid,SINC);
	Signal(semid,MUTEX);	
}
void consumaElementi(int semid,bufferCircolare* b){
	WaitZ(semid,SINC);
	int val[N];	
	for(int i = 0; i < N; i++){
		val[i] = b->elementi[i];
	}

	b->testa = 0;
	float media=Calcolamedia(b);
	float sigma=sqrt(Calcoladevstd(b,media));
	printf("[Consumatore %d] consumo elementi\n",getpid());
	printf("[Consumatore %d] media %f, varianza %f\n",getpid(),media,sigma);
	for(int i=0;i<N;i++){
		Signal(semid,SINC);
		
	}
}

float Calcolamedia(bufferCircolare* b){
	float temp=0;
	for(int i=0;i<N;i++){
		temp+=b->elementi[i];	
	}
	return (float)temp/N;	
}

float Calcoladevstd(bufferCircolare*b ,int m){
	float temp=0;
	for(int i=0;i<N;i++){
		temp+=(b->elementi[i]-m)^2;	
	}
	return (float)temp/(N-1);
}










