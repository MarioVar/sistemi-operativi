#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"header.h"
MonitorNegozio* m;
void* cliente(void* id){
	int i=(int)id;
	printf("[Cliente]Sono il thread cliente con id: %d\n",i);	
	int r=rand()%3;
	int costo;
	if(r==0)
		costo=10;
	if(r==1)
		costo=20;
	if(i==2)
		costo=30;
	for(int k=0;k<3;k++){
		inserisci_acquisto(i,costo);
		sleep(1);
	}
pthread_exit(0);
}
void* gestore(void* id){
		int i=(int)id;
	printf("[Gestore] Sono il thread gestore id=%d\n",i);
	for(int i=0;i<4;i++){
		sleep(2);
		for(int j=1;j<4;j++)
			completa_acquisto(j);		
	}
pthread_exit(0);
}
int main(){
	pthread_t thread[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	m=(MonitorNegozio*)malloc(sizeof(MonitorNegozio));
	inizializza();
	for(int i=0;i<4;i++){
		if(i==0)
			pthread_create(&thread[i],&attr,gestore,(void*)i);
		else
			pthread_create(&thread[i],&attr,cliente,(void*)i);	
	}
	for(int i=0;i<4;i++){
		pthread_join(thread[i],NULL);
		printf("Il thread %d è stato rimosso\n",i);	
	}
	rimuovi();
	pthread_attr_destroy(&attr);
return 0;
}
