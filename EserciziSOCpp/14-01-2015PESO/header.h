#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "../monitor/monitor.h"
#define nProc 5
#define N 10
#define SPAZIO_DISP 0
#define	RICHIESTA_DISP 1
typedef struct{
	unsigned int posizione;
	pid_t pid;
}richiesta;
typedef struct{
	int testa;
	int coda;
	int msg_disp;
	int spazio_disp;
	int posattuale;
}Gestione;
void scrittura(richiesta* r,Monitor* m,Gestione* g);
void schedula(richiesta* r,Monitor* m,Gestione* g);
