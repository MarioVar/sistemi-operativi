#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include"../monitor/monitor.h"
#include"magazzino.h"
int iniziofornitura(Monitor*m , scaffale *s){
	enter_monitor(m);
	int i=0;
	if(livello_scorte==N)//se non c'è spazio
		wait_condition(m,SPAZIODISP);
	while((i<N)&&(s[i].stato!=libero))
		i++;
	s[i].stato=in_uso;
	livello_scorte++;
	leave_monitor(m);
	return i;
}
void finefornitura(Monitor *m){
	signal_condition(m,PRODDISP);
}
void fornitura(Monitor *m ,scaffale *s){
	int index=iniziofornitura(m,s);
	printf("Sono il processo fornitore, il mio pid e' %d\n",getpid());
	s[index].stato=occupato;
	sleep(2);
	s[index].id_fornitore=getpid();
	printf("La struttura dati e' stata aggiornata in posizione %d con il valore %d, dal processo con pid %d \n",index,s[index].id_fornitore,getpid());
	finefornitura(m);
	
}
int inizioacquisto(Monitor* m,scaffale*s){
	int i=0;
	enter_monitor(m);
	if(livello_scorte==0)
		wait_condition(m,PRODDISP);
	while((i<N)&&(s[i].stato!=occupato))
		i++;
	s[i].stato=in_uso;
	livello_scorte--;
	leave_monitor(m);
	return i;
}
void fineacquisto(Monitor*m){
	signal_condition(m,SPAZIODISP);
}
void acquisto(Monitor *m,scaffale *s){
	int index=inizioacquisto(m,s);
	printf("Sono il processo CLIENTE, il mio pid e' %d, ho acquistato in posizione %d\n",getpid(),index);
	s[index].stato=libero;
	fineacquisto(m);
}
