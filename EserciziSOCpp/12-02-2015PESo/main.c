#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"header.h"
void * richiedi(void* mon){
	MonitorElaborazioni* m=(MonitorElaborazioni*)mon;
	int noperandi=(rand()%3)+2;
	inserisci_buffer(m,noperandi);
pthread_exit(0);
}
void* elabora(void* mon){
	MonitorElaborazioni* m=(MonitorElaborazioni*)mon;
	for(int i=0;i<3;i++)
		preleva_buffer(m);
pthread_exit(0);
}
int main(){
	pthread_t Richiedenti[4];
	pthread_t Elaboratori[2];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	MonitorElaborazioni* m=(MonitorElaborazioni*)malloc(sizeof(MonitorElaborazioni));
	Inizializza(m);
	for(int i=0;i<4;i++)
		pthread_create(&Richiedenti[i],&attr,richiedi,(void*)m);
	for(int i=0;i<2;i++)
		pthread_create(&Elaboratori[i],&attr,elabora,(void*)m);

	for(int i=0;i<4;i++){
		pthread_join(Richiedenti[i],NULL);
		printf("Thread Richiedente %d terminato\n",i);	
	}
	for(int i=0;i<2;i++){
		pthread_join(Elaboratori[i],NULL);
		printf("Thread Elaboratore %d terminato\n",i);	
	}
	Rimuovi(m);
	pthread_attr_destroy(&attr);
return 0;
}
