#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"header.h"
void client(int endnow){
	messaggio m,m1;
for(int i=0;i<5;i++){
	if(endnow){
		m.a=END;
		m.b=END;	
	}
	else{
		m.a=rand()%11;
		m.b=rand()%11;	
	}
	m.pid=getpid();
	m.tipo=getpid();
	msgsnd(coda_richiesta,(void*)&m,sizeof(messaggio)-sizeof(long),0);
	printf("[%d]Messaggio inviato a=%d b=%d\n",getpid(),m.a,m.b);
	msgrcv(coda_risposta,(void*)&m1,sizeof(messaggio)-sizeof(long),getpid(),0);
	printf("[%d]Ho ricevuto il messaggio prodotto=%d (a=%d,b=%d)\n",getpid(),m1.prodotto,m.a,m.b);
}
}
void* Manager(void* buffer){
	printf("[Manager]sono pronto!\n");
	messaggio* b=(messaggio*)buffer;
	messaggio m;
	for(int i=0;i<N;i++){
		b[i].stato=libero;	
	}
	int i=0;
	while(1){
	bytercv=(int)msgrcv(coda_richiesta,(void*)&m,sizeof(messaggio)-sizeof(long),0,IPC_NOWAIT);
	if(bytercv>0){
		printf("[Manager]Messaggio ricevuto!\n");
		if((m.a==END)&&(m.b==END)){
			for(int i=0;i<2;i++)
				pthread_cancel(worker[i]);
			free(b);
			pthread_exit(0);
		}
		b[i].a=m.a;
		b[i].b=m.b;
		b[i].pid=m.pid;
		b[i].prodotto=0;
		b[i].tipo=m.tipo;
		b[i].stato=occupato;
		i++;
		if(i==N)
			i=0;	
	}
	sleep(1);
	}
}
void* Worker(void* buffer){
	printf("[Worker]sono pronto!\n");
	int i=0;
	messaggio m;
	messaggio* b=(messaggio*)buffer;
	while(1){
		pthread_mutex_lock(&mutex);
		while((i<N)&&(b[i].stato!=occupato)){
			i++;
			if(i==N)
			i=0;
		}
		b[i].prodotto=(b[i].a)*(b[i].b);
		m.pid=b[i].pid;
		m.tipo=b[i].pid;
		m.a=b[i].a;
		m.b=b[i].b;
		m.prodotto=b[i].prodotto;
		b[i].stato=libero;
		pthread_mutex_unlock(&mutex);
		msgsnd(coda_risposta,(void*)&m,sizeof(messaggio)-sizeof(long),0);
	}
}

void server(){
	printf("[Server]Sono Pronto!\n");
	pthread_attr_t attr;
	pthread_mutex_init(&mutex,NULL);
	pthread_attr_init(&attr);
	messaggio* buffer=(messaggio*)malloc(N*sizeof(messaggio));
	pthread_create(&manager,&attr,Manager,(void*)buffer);
	for(int i=0;i<2;i++)
			pthread_create(&worker[i],&attr,Worker,(void*)buffer);
}


