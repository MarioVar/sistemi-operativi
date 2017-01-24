#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include"clientServer.h"
void client(int fine){
for(int i=0;i<15;i++){
	srand(getpid()+rand());
	pid_t pid=getpid();
	messaggio m,m1;
	m.tipo=codaCS;
	m.pid=pid;
	if(!fine){
		m.a=rand()%101;
		m.b=rand()%101;
	}
	else{
		m.a=END;
		m.b=END;	
	}
	msgsnd(idcoda1,(void*)&m,sizeof(messaggio)-sizeof(long),0);
	msgrcv(idcoda2,(void*)&m1,sizeof(messaggio)-sizeof(long),codaCS,0);
	printf("\n[%d]Messaggio ricevuto dal server:\n           _MESSAGGIO_        \npidClient=%d     PRODOTTO=%d        A=%d      B=%d       \n\n",pid,m1.pid,m1.prodotto,m1.a,m1.b);
}
}

void* svolgimento(void* dati){
	pthread_mutex_lock(&mutex);
	Dati *d =(Dati*)dati;
	messaggio m;
	m.prodotto=(d->a)*(d->b);
	m.pid=d->pid;
	m.a=d->a;
	m.b=d->b;
	m.tipo=codaCS;
	msgsnd(idcoda2,(void*)&m,sizeof(messaggio)-sizeof(long),0),
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
void server(){
	messaggio m;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_t thread;
	pthread_mutex_init(&mutex,NULL);
	Dati* d=(Dati*)malloc(sizeof(messaggio));
	int i=0;
	int x,y;
	pid_t pid;
	while((m.a!=END)&&(m.b!=END)){
		msgrcv(idcoda1,(void*)&m,sizeof(messaggio)-sizeof(long),codaCS,0);
		d->a=m.a;
		d->b=m.b;
		d->pid=m.pid;
		pthread_create(&thread,&attr,svolgimento,(void*)d);
	}
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
	free(d);
	printf("[SERVER] Terminazione !\n");
	exit(0);
}
