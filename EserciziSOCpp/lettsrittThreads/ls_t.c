/*			lettori scrittori con thread e starvation scrittori			*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"ls_t.h"

int main(){
pthread_attr_t attr;
pthread_t thread[NUMTHREAD];
int thr;
/*inizializzazione strutture*/
for(int i=0;i<N;i++){
	b.stato[i]=libero;
	b.buffer[i]=0;
	b.numlettori=0;
}
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&ok_lettura,NULL);
pthread_cond_init(&ok_scrittura,NULL);
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
/*generazione lettori scrittori*/
for(int i=0;i<NUMTHREAD;i++){
	if(i%2){
		printf("Sono il thread %d, sono un lettore\n",i);
		sleep(1);
		pthread_create(&thread[i],(void*)&attr,lettura,(void*)i);	
	}
	else{
		printf("Sono il thread numero %d,sono uno scrittore\n",i);
		pthread_create(&thread[i],(void*)&attr,scrittura,(void*)i);	
	}
}
/*attesa terminazione threads*/
for(int i=0;i<NUMTHREAD;i++){
	pthread_join(thread[i],NULL);
	printf("Il thread numero %d e' terminato\n",i);
}
printf("<Master controller> Tutti i thread hanno terminato la loro esecuzione\n"); 
/*dellocazione strutture*/
pthread_mutex_destroy(&mutex);
pthread_cond_destroy(&ok_lettura);
pthread_cond_destroy(&ok_scrittura);
pthread_attr_destroy(&attr);
pthread_exit(0);
}
