#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"header.h"
void Inizializza(GestioneIO * g){
	pthread_mutex_init(&(g->mutex),NULL);
	pthread_cond_init(&(g->spazio),NULL);
	g->coda=0;
	g->nelem=0;
	g->testa=0;
	for(int i=0;i<N;i++){
		g->vettore[i].indirizzo=0;
		g->vettore[i].dato=0;	
	}
}
void Produci(GestioneIO * g, Buffer * b){
	pthread_mutex_lock(&(g->mutex));
	while(g->nelem==N)
		pthread_cond_wait(&(g->spazio),&(g->mutex));
	g->vettore[g->testa].indirizzo=b->indirizzo;
	g->vettore[g->testa].dato=b->dato;
	printf("Ho prodotto il valore (%d,%d) in posizione %d\n",g->vettore[g->testa].indirizzo,g->vettore[g->testa].dato,g->testa);
	g->testa=(g->testa+1)%N;
	g->nelem=g->nelem+1;
	pthread_mutex_unlock(&(g->mutex));	
}
int Consuma(GestioneIO * g, Buffer * b){
	pthread_mutex_lock(&(g->mutex));
	if(g->nelem==0){
		pthread_mutex_unlock(&(g->mutex));
		return 1;
	}
	else{
		b->indirizzo=g->vettore[g->coda].indirizzo;
		b->dato=g->vettore[g->coda].dato;
		g->coda=(g->coda+1)%N;
		g->nelem=g->nelem-1;
		pthread_cond_signal(&(g->spazio));	
		pthread_mutex_unlock(&(g->mutex));
		return 0;
	}
}
