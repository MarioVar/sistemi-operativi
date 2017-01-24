#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include"calcetto.h"
void lettura(partita * p){
	pthread_mutex_lock(&(p->mutex));
	while(p->occupato_da_scrittore==1)
		pthread_cond_wait(&(p->ok_lettura),&(p->mutex));
	p->nlettori++;
	pthread_mutex_unlock(&(p->mutex));
	printf("[Score] Team A <%d>-Team B <%d>\n",p->goal_A,p->goal_B);
	pthread_mutex_lock(&(p->mutex));
	p->nlettori--;
	if(p->nlettori==0);
		pthread_cond_signal(&(p->ok_scrittura));
	pthread_mutex_unlock(&(p->mutex));
	
}
void aggiorna_risultato(partita * p,int goal,int seleziona){
	pthread_mutex_lock(&(p->mutex));
	int goalA,goalB;
	goalA=p->goal_A;
	goalB=p->goal_B;
	while((p->occupato_da_scrittore==1)||(p->nlettori>0))
		pthread_cond_wait(&(p->ok_scrittura),&(p->mutex));
	p->occupato_da_scrittore=1;
	switch(seleziona){
		case TEAM_A:
			p->goal_A+=goal;
			break;
			
		case TEAM_B:
			p->goal_B+=goal;
			break;
		default:
			printf("Errore in aggiornamento\n");
			pthread_exit(0);
			break;
	}
	if(goalA<(p->goal_A))
		printf("[telecronista]ATTENZIONE Goal squadra A\n");
	else if(goalB<p->goal_B)
		printf("[telecronista]ATTENZIONE Goal squadra B\n");
	pthread_cond_signal(&(p->ok_lettura));
	p->occupato_da_scrittore=0;
	pthread_mutex_unlock(&(p->mutex));
}
