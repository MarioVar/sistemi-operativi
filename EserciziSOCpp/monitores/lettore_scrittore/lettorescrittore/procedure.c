#include<sys/types.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>

#include"../monitor/monitor.h"
#include"ls.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
/*
*	void init_monitor (Monitor*, int); 
*	void enter_monitor(Monitor*);
*	void leave_monitor(Monitor*);
*	void remove_monitor(Monitor*);
*	void wait_condition(Monitor*,int);
*	void signal_condition(Monitor*,int);
*/

void iniziolettura(memory* mem,Monitor* M){
	enter_monitor(M);
		if(mem->occupato && mem->numlettori==0)
			wait_condition(M,SYNC_L);
		mem->occupato=1;
		mem->numlettori=mem->numlettori+1;
		signal_condition(M,SYNC_L);
			
}
void inizioscrittura(memory* mem,Monitor* M){
	enter_monitor(M);
		if(mem->occupato)
			wait_condition(M,SYNC_S);
		mem->occupato=1;
		leave_monitor(M);
}

void finelettura(Monitor* m,memory* buf){
	enter_monitor(m);
        buf->numlettori=buf->numlettori-1;
        if (buf->numlettori==0) {// se sono finiti i lettori lo segnala agli scrittori
     		buf->occupato=0;
		signal_condition(m,SYNC_S);
	}
        else // altrimenti lascia il monitor
        	leave_monitor(m);
	
}
void finescrittura(Monitor* m,memory* buf){
	enter_monitor(m);
	if (queue_condition(m,SYNC_S)>0) // sblocco di eventuali altri scrittori
		signal_condition(m,SYNC_S);
        else if (queue_condition(m,SYNC_L)>0) { // sblocco di eventuali altri lettori
		// while (queue_condition(m,SYNCHL) ... sblocco di tutti i lettori
		//buf->occupato =0;
     		signal_condition(m,SYNC_L);
	}
        else { // altrimenti lascia il monitor
        	buf->occupato =0;
		leave_monitor(m);
	}
}

void Produzione(memory* buf,Monitor* m){
	inizioscrittura(buf,m);
    	buf->messaggio =(rand()%100);
	sleep(1);
    	printf ("Valore scritto: <%d> \n", (int)buf->messaggio);
	finescrittura(m,buf);
}
void Lettura(memory* buf,Monitor* m){
	iniziolettura(buf,m);

	/*********Lettura********/
	//sleep(1); // per simulare un ritardo di lettura
        printf("Valore letto=<%d>, numero lettori=%d \n",(int)buf->messaggio,buf->numlettori);
	finelettura(m,buf);
}
