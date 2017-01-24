#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include <sys/ipc.h>
#include<sys/types.h>
#include"header.h"
/*Il Server deve accumulare i messaggi ricevuti in un buffer; quando saranno stati
accumulati 10 messaggi, esso lì invierà ad un terzo processo denominato Printer*/
void server(int bid,int idp){
	messaggio m;
	int count=0;
	int temp[10];
	while(1){
		msgrcv(bid,(void*)&m,sizeof(m)-sizeof(long),BUFFER,0);
		m.tipo=PRINTER;
		count++;
		temp[count]=m.idClient;
		if(count%10==0){
			count=0;
			for(int i=0;i<10;i++){
				m.idClient=temp[i];
				msgsnd(idp,(void*)&m,sizeof(m)-sizeof(long),0);
				printf("[SERVER] Ho inviato il messaggio %d di 10\n",i+1);
			}
		}	
	}
}
/*I messaggi
dovranno contenere il PID del processo Client che ha generato il messaggio, e ciascun Client dovrà
generare 15 messaggi, attendendo 1 secondo tra un messaggio e l’altro*/
void client(int bid){
	messaggio m;
	m.tipo=BUFFER;
	m.idClient=getpid();
	msgsnd(bid,(void*)&m,sizeof(m)-sizeof(long),0);
	printf("[CLIENT <%d>] Messaggio inviato\n",getpid());

}
/*Printer: stampa a
video i messaggi ricevuti insieme ad un numero progressivo che conti i messaggi ricevuti.*/
void printer(int idp){
	messaggio m;
	int count=0;
	while(1){
		msgrcv(idp,(void*)&m,sizeof(m)-sizeof(long),PRINTER,0);	
		count++;
		printf("\n[PRINTER] Ho ricevuto il messaggio di -%d  *totale messaggi ricevuti: %d\n\n",m.idClient,count);
			
	}
}
