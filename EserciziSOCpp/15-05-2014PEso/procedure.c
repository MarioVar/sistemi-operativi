#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include"pizzeria.h"
void aggiungi_consegna(struct Monitor * m,int pizza,int cliente){
	pthread_mutex_lock(&(m->mutex));
	int i=0;

	while(m->nOrdini==5)
		pthread_cond_wait(&(m->ok_spazio_consegne),&(m->mutex));
	while((m->c[i].stato!=VUOTO)&&(i<5))
		i++;
	m->c[i].stato=PRONTO;
	m->c[i].pizza=pizza;
	m->c[i].cliente=cliente;
	pthread_cond_signal(&(m->ok_nuova_consegna));
	m->nOrdini=m->nOrdini+1;
	printf("Sono il thread pizzaiolo, ho ricevuto l'ordine di una pizza %d. ToalaeOrdini=%d Cliente=%d\n",m->c[i].pizza,m->nOrdini,m->c[i].cliente);
	pthread_mutex_unlock(&(m->mutex));
}
int inizia_consegna(struct Monitor * m){
	int i=0;
	pthread_mutex_lock(&(m->mutex));
	while(m->nOrdini==0){
		pthread_cond_wait(&(m->ok_nuova_consegna),&(m->mutex));
	}
	while((i<5)&&(m->c[i].stato!=PRONTO)){
		printf("i=%d",i);		
		i++;
		printf("i=%d",i);	
	}
	m->c[i].stato=IN_CONSEGNA;
	printf("[Fattorino] L'ordine %d e' in stato %d",i,m->c[i].stato);
	return i;
	
}
void fine_consegna(struct Monitor * m, int indice_consegna){
	pthread_mutex_lock(&(m->mutex));
	m->c[indice_consegna].stato=VUOTO;
	m->nOrdini=m->nOrdini-1;
	printf("Sono il thread fattorino, ho effettuato la consegna %d",indice_consegna);
	pthread_cond_signal(&(m->ok_spazio_consegne));
	pthread_mutex_unlock(&(m->mutex));
}
