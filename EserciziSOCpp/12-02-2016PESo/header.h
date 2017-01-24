#include<pthread.h>
#define N 5
#define T_manager 1
#define T_worker 4
#define NumThread 5
typedef struct{
	int *  vettore;
	int dimensione;
	int nelem;
	int coda;
	int testa;
	pthread_mutex_t mutex;
	pthread_cond_t spazio_disp;
	pthread_cond_t elem_disp;
}Vettore;
typedef struct{
	int conteggio;
	int somma;
	pthread_mutex_t mutexsum;
}Risultato;
extern Vettore* v1;
extern Vettore* v2;
void Somma(Risultato* r,int v,int  z);
void Inizializza(Vettore * v, int dimensione);
void Inserisci_elemento(Vettore * v, int elem,int i);
int Preleva_elemento(Vettore *v,int i);
void Rimuovi(Vettore* v);
