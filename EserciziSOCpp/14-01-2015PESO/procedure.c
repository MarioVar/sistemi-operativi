#include"header.h"
void scrittura(richiesta* r,Monitor* m,Gestione* g){
	enter_monitor(m);
	if(g->spazio_disp==0)
		wait_condition(m,SPAZIO_DISP);
	r[g->testa].pid=getpid();
	r[g->testa].posizione=rand()%20;
	printf("Scrittura: richiedo la scrittura del valore %d in posizione %d \n ",r[g->testa].pid,r[g->testa].posizione);
	g->testa++;
	g->spazio_disp--;
	g->msg_disp++;
	signal_condition(m,RICHIESTA_DISP);
	leave_monitor(m);
}
void schedula(richiesta* r,Monitor* m,Gestione* g){
	while(1){
	enter_monitor(m);
	if(g->msg_disp==0)
		wait_condition(m,RICHIESTA_DISP);
	int dato=r[g->testa].pid;
	int posizione=r[g->testa].posizione;
	int t=posizione-(g->posattuale);
	if(t<0)
		t=-t;
	printf("Tempo da attendere per la scrittura: %d\n",t);
	leave_monitor(m);
	sleep(t);
	enter_monitor(m);
	printf("Scheduler:Ho servito la richiesta  (pid=%d,posizione%d)\n ",r[g->testa].pid,r[g->testa].posizione);
	g->posattuale=posizione;
	g->testa--;
	g->spazio_disp++;
	g->msg_disp--;
	signal_condition(m,SPAZIO_DISP);
	leave_monitor(m);
	}
}
