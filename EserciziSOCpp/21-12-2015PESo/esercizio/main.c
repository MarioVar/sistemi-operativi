#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"header.h"
void * produci(void* g){
	GestioneIO * ges=(GestioneIO*) g;
	Buffer b;
	int indirizzo=rand()%11;
	int dato=rand()%11;
	b.indirizzo=indirizzo;
	b.dato=dato;
	for(int i=0;i<3;i++){
		Produci(ges,&b);
		b.indirizzo=b.indirizzo+1;	
		b.dato=b.dato+1;
		sleep(1);
	}
pthread_exit(0);
}
void* consuma(void* g){
	Buffer b;
	int val;
	GestioneIO* ges=(GestioneIO*)g;
	for(int i=0;i<4;i++){
		while(Consuma(ges,&b)==0){
			printf("[CONSUMATORE](iterazione %d)Valore prelevato dal buffer: indirizzo:%d dato=%d\n",i,b.indirizzo,b.dato);
		}
		printf("[CONSUMATORE] BUFFER VUOTO \n");		
		sleep(3);
	}
		
pthread_exit(0);
}

int main(){
	pthread_t thread[6];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	GestioneIO* g=(GestioneIO*)malloc(sizeof(GestioneIO));
	Inizializza(g);

	for(int i=0;i<3;i++)
		pthread_create(&thread[i],&attr,produci,(void*)g);
	for(int i=3;i<6;i++)
		pthread_create(&thread[i],&attr,consuma,(void*)g);

	for(int i=0;i<6;i++){
		pthread_join(thread[i],NULL);
		printf("Thread %d è termianto\n",i);
	}
	pthread_mutex_destroy(&(g->mutex));
	pthread_attr_destroy(&attr);
	pthread_cond_destroy(&(g->spazio));
	free(g);
	
return 0;
}
