#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include"../monitor/monitor.h"
#include"prodcons.h"
/*
*precondition: il buffer non è inizializzato
*postcondition: il buffer è stato inizializzato
*/
void initBuffer(buffer *b){
	for(int i=0;i<N;i++){
		b->stato[i]=libero;
		b->spazio_disp=N;
		b->msg_disp=0;
		b->buffer[i]=0;	
	}
}
/*
*postcondition:verificare se è possibile produrre
*/
int inizioProduzione(Monitor * m,buffer * b)
{
	enter_monitor(m);
	int i=0;;

	while((i<N)&&(b->stato[i]==occupato)){
		
		wait_condition(m,OK_PROD);
		i++;	
	}
	return i;
	
}

/*
*postcondition:ho prodotto il valore, segnalo i consumatori
*/
void fineProduzione(Monitor* m,buffer* b){
	if(b->spazio_disp>0)
		b->spazio_disp=b->spazio_disp-1;
	if(b->msg_disp<N)
		b->msg_disp=b->msg_disp+1;
	signal_condition(m,OK_CONS);
	leave_monitor(m);

}
/*
*precondition:il buffer ha almeno un dato da consumare
*postcondition:consumo
*/
int inizioConsumo(Monitor * m,buffer *b){
	enter_monitor(m);
	int i=0;
	while((i<N)&&(b->stato[i]==libero)){
		
		wait_condition(m,OK_CONS);	
		i++;
	}
	return i;
	
}
/*
*postcondition:il dato è stato consumato, segnalo i produttori
*/
void fineConsumo(Monitor* m,buffer* b){
	if(b->msg_disp>0)
		b->msg_disp=b->msg_disp-1;
	if(b->spazio_disp<N)
		b->spazio_disp=b->spazio_disp+1;
	signal_condition(m,OK_PROD);
	leave_monitor(m);
}
/*
*effettuo la produzione
*/
void produzione(Monitor*m,buffer *b ){
	int i=inizioProduzione(m,b);
	b->buffer[i]=(rand()%20);
	printf("<%d> Ho prodotto il dato %d in posizione %d\n",getpid(),b->buffer[i],i);
	fineProduzione(m,b);
	
}

/*
*effettuo il consumo
*/
void consumo(Monitor *m,buffer *b){
	int i=inizioConsumo(m,b);
	int temp=b->buffer[i];
	printf("<%d> Ho consumato il dato %d in posizione %d\n",getpid(),temp,i);
	fineConsumo(m,b);
}
