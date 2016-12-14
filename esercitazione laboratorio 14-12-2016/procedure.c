#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"header.h"
void aggiungi_volo(gestorevolo* g,int id){
	pthread_mutex_lock(&(g->mutex));
	int i=0;
	while(g->spazio==0){
		pthread_cond_wait(&(g->spazio_disp),&(g->mutex));
	}
	while((i<N)&&(g->stato[i]!=libero))
		i++;
	g->stato[i]=in_uso;
	g->spazio--;//devo decrementare prima di fare la unlock perchè se lo faccio in (*) poi tutti i voli verranno inseriti perchè il mutex è rilasciato e il processo si addormenta!!
	pthread_mutex_unlock(&(g->mutex));
	sleep(1);

	pthread_mutex_lock(&(g->mutex));	
	g->vettore[i].id=id;
	g->vettore[i].quota=0;	
	// (*)
	g->stato[i]=occupato;
	printf("Ho aggiunto il volo <%d>\n",g->vettore[i].id);
	pthread_mutex_unlock(&(g->mutex));
}
void rimuovi_volo(gestorevolo*g, int id){
	int index,trovato=0,i=0;
	pthread_mutex_lock(&(g->mutex));
	while((i<N)&&(!trovato)){
		if((g->vettore[i].id==id)&&(g->stato[i]==occupato)){
			index=i;
			trovato=1;
		}		
		i++;	
	}
	if(trovato){
		g->stato[index]=in_uso;
		g->spazio++;
	}
	else
		printf("il volo con id %d non è presente tra i voli attuali\n",id);
	pthread_mutex_unlock(&(g->mutex));
	sleep(1);
	pthread_mutex_lock(&(g->mutex));
	if(trovato){
		g->stato[i]=libero;
		pthread_cond_signal(&(g->spazio_disp));
		printf("Il volo <%d> è stato rimosso\n",g->vettore[i].id);	
	}
	pthread_mutex_unlock(&(g->mutex));
}
void aggiorna_quota(gestorevolo *g, int id,int nuovaquota){
	pthread_mutex_lock(&(g->mutex));
	int index,trovato=0,i=0;
	while((i<N)&&(!trovato)){
		if(g->stato[i]==1000)
			printf("*********[aggiorna_quota]stato[%d]=%d\n\n",i,g->stato[i]);
		if((g->vettore[i].id==id)&&(g->stato[i]==occupato)){
			index=i;
			trovato=1;
		}		
		i++;	
	}
	//devo usare index e non i perchè nel caso in cui non trovi nulla i arriva ad un valore >N => non ti trovi
	g->stato[index]=in_uso;
	pthread_mutex_unlock(&(g->mutex));
	sleep(rand()%4+1);
	pthread_mutex_lock(&(g->mutex));
	g->stato[index]=occupato;
	g->vettore[index].quota=nuovaquota;
	printf("Il volo <%d> è salito a quota %d\n",g->vettore[index].id,g->vettore[index].quota);
	pthread_mutex_unlock(&(g->mutex));
}
