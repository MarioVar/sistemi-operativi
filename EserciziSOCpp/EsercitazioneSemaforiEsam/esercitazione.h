#ifndef __ESERCITAZIONE
#define __ESERCITAZIONE

#define PATH_SHM "."
#define CHAR_SHM 'a'

#define PATH_SEM "."
#define CHAR_SEM 'b'


#define N 5

#define SINC 0
#define MUTEX 1

typedef struct{
	int elementi[N];
	int testa;
	int coda;

}bufferCircolare;


//semafori
void Wait(int sem_id,int numsem);
void WaitZ(int sem_id,int numsem);
void Signal(int sem_id,int numsem);
int leggi_valore(int id_sem,int semaforo);
void produciElemento(int sem_id,bufferCircolare* buf);
void consumaElementi(int sem_id,bufferCircolare* buf);
float Calcoladevstd(bufferCircolare*b ,int m);
float Calcolamedia(bufferCircolare* b);
#endif

