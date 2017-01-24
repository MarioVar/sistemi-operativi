#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/msg.h>
#include<sys/types.h>
#include"mex.h"
void richiestaC(){
	messaggio m;
	m.tipo=CLIENT;
	m.pidC=getpid();
	int msg=msgsnd(codaClient,(void*)&m,sizeof(m)-sizeof(long),0);
	if(msg==-1)
		perror("Errore invio messaggio client");
}
void inoltroB(){
	messaggio m1;
	while(1){
		int r=msgrcv(codaClient,(void*)&m1,sizeof(m1)-sizeof(long),CLIENT,0);
		if(r==-1)
			perror("Errore ricezione balacer");
	
		m1.tipo=SERVER;
		int msg=msgsnd(codaBalancer,(void*)&m1,sizeof(m1)-sizeof(long),0);
		printf("[Balancer] Messaggio inoltrato");
		if(msg==-1)
			perror("Errore invio messaggio client");
	}
}
void Server(){
	messaggio m;
	
		int s=msgrcv(codaBalancer,(void*)&m,sizeof(m)-sizeof(long),SERVER,0);
		printf("[%d]Sono il processo SERVER, ho ricevuto il messaggio di %d\n",getpid(),m.pidC);
	
}
