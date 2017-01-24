#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include"ls_t.h"
int spaziodisp=N;
int messaggiodisp=0;
void iniziolettura(){
	pthread_mutex_lock(&mutex);
	while(messaggiodisp==0)
		pthread_cond_wait(&ok_lettura,&mutex);
	b.numlettori++;
	pthread_mutex_unlock(&mutex);
};
void finelettura(){
	pthread_mutex_lock(&mutex);
	//il lettore ha letto tutto il vettore
	for(int i=0;i<N;i++)
		b.stato[i]=letto;
	b.numlettori--;
	if(b.numlettori==0)
		pthread_cond_signal(&ok_scrittura);	
	else
		pthread_cond_signal(&ok_lettura);
	pthread_mutex_unlock(&mutex);
};
int inizioscrittura(){
	int i=0;
	pthread_mutex_lock(&mutex);
	while((spaziodisp!=0)&&(b.stato[i]==occupato))
		i++;
	while(spaziodisp==0)
		pthread_cond_wait(&ok_scrittura,&mutex);
	printf("\nLA CASELLA %d E' Occupata\n",i);
	b.stato[i]=occupato;
	return i;
	
};
void finescrittura(int i){
	spaziodisp--;
	messaggiodisp++;
	if(spaziodisp==0)
		b.stato[i]==libero;
	pthread_cond_signal(&ok_lettura);
	pthread_mutex_unlock(&mutex);
};
void * lettura(void * id){
	iniziolettura();
	int * idlettore=(int*)id;
	for(int i=0;i<N;i++){
		if(b.stato[i]==occupato)
			printf("Sono il lettore %d, ho letto il dato %d, in posizione %d\n",(int)idlettore,b.buffer[i],i);
		else
			printf("Nessun dato presente in posizione %d\n",i);
	}
	finelettura();
};
void * scrittura(void* id){
	int i = inizioscrittura();
	int * idscrittore=(int*) id;
	b.buffer[i]=rand();
	printf("Sono lo scrittore  %d, ho scritto il dato %d, in posizione %d\n",(int)idscrittore,b.buffer[i],i);
	finescrittura(i);
};
