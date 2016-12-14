#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"header.h"
gestorevolo * g;
void* nuovo_volo(void* i){
	int id=(int)i;
	aggiungi_volo(g,id);
	aggiorna_quota(g,id,1000);
	aggiorna_quota(g,id,2000);
	aggiorna_quota(g,id,1000);
	rimuovi_volo(g,id);
	pthread_exit(0);
}
int main(){
	pthread_attr_t attr;
	pthread_t volo[N];
	int i;
	g=(gestorevolo*)malloc(sizeof(gestorevolo));
	pthread_mutex_init(&(g->mutex),NULL);
	pthread_cond_init(&(g->spazio_disp),NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	g->spazio=N;
	for(int i=0;i<N;i++){
		g->vettore[i].id=-1;
		g->vettore[i].quota=0;
		g->stato[i]=libero;	
	}
	for(i=0;i<5;i++)
		pthread_create(&volo[i],&attr,nuovo_volo,(void*)i);
	for(i=0;i<5;i++){
		pthread_join(volo[i],NULL);
		printf("Il thread %d è terminato\n",i);
	}
	pthread_mutex_destroy(&(g->mutex));	
	pthread_cond_destroy(&(g->spazio_disp));
	pthread_attr_destroy(&attr);
	free(g);
}
