#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"header.h"
Vettore* v1;
Vettore* v2;
void * manager(void* in){
	int i=(int)in;
	int a,b;
	printf("[%d]Sono il thread Manager\n",i);
	for(int i=0;i<20;i++){
		a=rand()%5;
		b=rand()%5;
		if(i%2)
			Inserisci_elemento(v1,a,1);
		else
			Inserisci_elemento(v2,b,2);	
	}
	pthread_exit(0);
}
void * worker(void* i){
	int e1,e2;
	Risultato* r=(Risultato*) i;
	printf("Sono il thread Worker\n");
	while(r->conteggio!=10){
		e1=Preleva_elemento(v1,1);
		e2=Preleva_elemento(v2,2);
		Somma(r,e1,e2);
		sleep(1);
	}
	pthread_exit(0);
}
int main(){
	pthread_t thread[NumThread];
	pthread_attr_t  attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	Risultato* r=(Risultato*)malloc(sizeof(Risultato));
	pthread_mutex_init(&(r->mutexsum),NULL);
	r->conteggio=0;
	r->somma=0;
	v1=(Vettore*)malloc(sizeof(Vettore));
	v2=(Vettore*)malloc(sizeof(Vettore));
	Inizializza(v1,N);
	Inizializza(v2,N);
	for(int i=0;i<NumThread;i++){
		if(i==0)
			pthread_create(&thread[i],&attr,manager,(void*)i);
		else
			pthread_create(&thread[i],&attr,worker,(void*)r);	
	}
	for(int i=0;i<NumThread;i++){
		pthread_join(thread[i],NULL);
		printf("Il thread %d è terminato\n",i);	
	}
	printf("[Main]Il valore della somma è %d\n",r->somma);
	Rimuovi(v1);
	Rimuovi(v2);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&(r->mutexsum));
	free(r);
	pthread_exit(0);
return 0;	
}
