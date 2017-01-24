#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"header.h"
void Somma(Risultato* r,int e1,int e2){
	pthread_mutex_lock(&(r->mutexsum));
	int Val;
	Val=e1*e2;
	r->somma=r->somma+Val;
	r->conteggio=r->conteggio+1;
	pthread_mutex_unlock(&(r->mutexsum));
}
void Inizializza(Vettore * v, int dimensione){
	pthread_mutex_init(&(v->mutex),NULL);
	pthread_cond_init(&(v->spazio_disp),NULL);
	pthread_cond_init(&(v->elem_disp),NULL);
	v->dimensione=N;
	v->nelem=0;
	v->coda=0;
	v->testa=0;
	v->vettore=(int*)malloc(N*sizeof(int));
	for(int i=0;i<N;i++)
		v->vettore[i]=0;
}
void Inserisci_elemento(Vettore * v, int elem,int i){
	pthread_mutex_lock(&(v->mutex));
	while(v->nelem==N)
		pthread_cond_wait(&(v->spazio_disp),&(v->mutex));
	v->vettore[v->testa]=elem;
	printf("[Manager]Ho aggiunto l'elemento %d in posizione %d nel Vettore %d\n",v->vettore[v->testa],v->testa,i);
	v->nelem=v->nelem+1;
	v->testa=(v->testa+1)%N;
	pthread_cond_signal(&(v->elem_disp));
	pthread_mutex_unlock(&(v->mutex));
}
int Preleva_elemento(Vettore *v,int i){
	pthread_mutex_lock(&(v->mutex));
	int e;
	while(v->nelem==0)
		pthread_cond_wait(&(v->elem_disp),&(v->mutex));
	e=v->vettore[v->coda];
	printf("[Worker]Ho prelevato il valore %d in posizione %d nel vettore %d\n",v->vettore[v->coda],v->coda,i);
	v->coda=(v->coda+1)%N;
	v->nelem=v->nelem-1;
	pthread_cond_signal(&(v->spazio_disp));
	pthread_mutex_unlock(&(v->mutex));
	return e;

}
void Rimuovi(Vettore* v){
	pthread_mutex_destroy(&(v->mutex));
	pthread_cond_destroy(&(v->spazio_disp));
	pthread_cond_destroy(&(v->elem_disp));
	free(v);
}
