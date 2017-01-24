#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include"calcetto.h"
void* aggiorna_score_squadraA(void * p){
	p=(partita*) p;
	int goal;
	for(int i=0;i<15;i++){
	goal=rand()%2;
	aggiorna_risultato(p,goal,TEAM_A);
	sleep(15);	
	}
	pthread_exit(0);
}
void* aggiorna_score_squadraB(void * p){
	p=(partita*) p;
	int goal;
	for(int i=0;i<15;i++){
	goal=rand()%2;
	aggiorna_risultato(p,goal,TEAM_B);
	sleep(15);	
	}
	pthread_exit(0);
}
void* leggi_score(void* p){
	p=(partita*) p;
	for(int i=0;i<18;i++){
	lettura(p);
	sleep(5);	
	}
}
int main(){
partita* p=(partita*)malloc(sizeof(partita));
/*definisco i thread*/
pthread_t thread[Nthread];
pthread_attr_t attr;
/*inizializo i thread*/
pthread_mutex_init(&(p->mutex),NULL);
pthread_cond_init(&(p->ok_lettura),NULL);
pthread_cond_init(&(p->ok_scrittura),NULL);
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
/*inizializazione struttura dati*/
p->goal_A=0;
p->goal_B=0;
p->nlettori=0;
p->occupato_da_scrittore=0;
/*creo i thread*/
for(int i=0;i<Nthread;i++){
	if(i==0){//thread che si occupa di aggiornare i risultati di a (TA)
		pthread_create(&thread[i],&attr,(void*) aggiorna_score_squadraA,(void*)p);
	}
	else if(i==1){//thread che si occupa di aggiornare i risultati di b (TB)
		pthread_create(&thread[i],&attr,(void*) aggiorna_score_squadraB,(void*)p);
	}
	else{//utenti di servizio
		pthread_create(&thread[i],&attr,(void*) leggi_score,(void*)p);
	}
}
/*attesa terminazione thread*/
for(int i=0;i<Nthread;i++){
	pthread_join(thread[i],NULL);
	printf("Il thread %d e' termianto\n",i);
}
/*rimozione strutture*/
pthread_mutex_destroy(&(p->mutex));
pthread_attr_destroy(&attr);
pthread_cond_destroy(&(p->ok_lettura));
pthread_cond_destroy(&(p->ok_scrittura));
pthread_exit(0);
return 0;
}
