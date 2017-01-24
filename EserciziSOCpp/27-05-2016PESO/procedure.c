#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"header.h"
void inizializza(){
	pthread_mutex_init(&(m->mutex),NULL);
	pthread_cond_init(&(m->spazio_disponibile),NULL);
	m->spazio_disp=N;
	m->fatturato=0;
	for(int i=0;i<N;i++){
		m->vettore[i].cliente=-1;
		m->vettore[i].stato=libero;
		m->vettore[i].costo=0;	
	}	
}
void rimuovi(){
	pthread_cond_destroy(&(m->spazio_disponibile));
	pthread_mutex_destroy(&(m->mutex));
	free(m);
}
void inserisci_acquisto(int id_cliente,int costo){
	pthread_mutex_lock(&(m->mutex));
	int i=0;
	while(m->spazio_disp==0){
		pthread_cond_wait(&(m->spazio_disponibile),&m->mutex);
	}
	while((i<N)&&(m->vettore[i].stato!=libero))
		i++;
	m->vettore[i].stato=in_uso;
	m->spazio_disp--;
	pthread_mutex_unlock(&(m->mutex));

	m->vettore[i].costo=costo;
	m->vettore[i].cliente=id_cliente;
	printf("[CLIENTE]Ho aggiunto l'acquisto del cliente %d in posizione %d|| costo=%d\n",m->vettore[i].cliente,i,m->vettore[i].costo);

	pthread_mutex_lock(&(m->mutex));
	m->vettore[i].stato=occupato;
	pthread_mutex_unlock(&(m->mutex));
}
void completa_acquisto(int id_cliente){
	pthread_mutex_lock(&(m->mutex));
	int i=0;
	while(i<N){
		if(m->vettore[i].cliente==id_cliente){
			m->fatturato=m->fatturato+m->vettore[i].costo;
			m->vettore[i].stato=libero;
			printf("[GESTORE]Il cliente %d ha effettuato ha speso %d nell acquisto %d\n",id_cliente,m->vettore[i].costo,i);	
		}
		i++;	
	}
	printf("[GESTORE]Fatturato totale=%d\n",m->fatturato);
	m->spazio_disp++;
	pthread_cond_signal(&(m->spazio_disponibile));
	pthread_mutex_unlock(&(m->mutex));
	
}
