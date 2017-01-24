#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include"pizzeria.h"
void * consegna(void * mon){
	printf("Sono il thread fattorino\n");
	struct Monitor * m=(struct Monitor*)mon;
	int index;
	for(int i=0;i<5;i++){
		index=inizia_consegna(m);
		sleep((rand()%3)+1);
		fine_consegna(m,index);
	}
	pthread_exit(NULL);
}
void * aggiungi(void * mon){
	printf("Sono il pizzaiolo\n");
	int id;
	struct Monitor * m=(struct Monitor*)mon;
	for(int i=0;i<15;i++){
		int pizza=(rand()%PIZZEDISP)+1;
		aggiungi_consegna(m,pizza,id);
		id ++;
		sleep(1);
	}
	pthread_exit(NULL);
}
int main(){
	pthread_t thread[N];
	pthread_attr_t attr;
	struct Monitor* m=(struct Monitor *)malloc(sizeof(struct Monitor));
	/*inizializzazione strutture*/
	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->ok_nuova_consegna),NULL);
	pthread_cond_init(&(m->ok_spazio_consegne),NULL);
	pthread_attr_init(&attr);
	for(int i=0;i<5;i++){
		m->c[i].stato=VUOTO;
		m->c[i].cliente=0;
		m->c[i].pizza=0;
	}
	m->nOrdini=0;
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	/*CREAZIONE THREAD*/
	for(int i=0;i<3;i++){//thread fattorini
		pthread_create(&thread[i],&attr,(void*)consegna,(void*)m);	
	}
	//thread pizzaiolo
	pthread_create(&thread[4],&attr,(void *) aggiungi,(void*)m);

	/*RIMOZIONE THREAD*/
	for(int i=0;i<N;i++){
		pthread_join(thread[i],NULL);
		printf("[%d] E' terminato\n",i);	
	}
	/*rimozione strutture*/
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&(m->mutex));
	pthread_cond_destroy(&(m->ok_nuova_consegna));
	pthread_cond_destroy(&(m->ok_spazio_consegne));
	free(m->c);
	pthread_exit(0);
return 0;
}
