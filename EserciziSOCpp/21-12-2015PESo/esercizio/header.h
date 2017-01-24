#define N 10
#include<pthread.h>
typedef struct {
	int indirizzo;
	int dato;
} Buffer;
typedef struct {
	Buffer vettore[N];
	int coda;
	int nelem;
	int testa;
	pthread_mutex_t mutex;
	pthread_cond_t spazio;
} GestioneIO;
void Inizializza(GestioneIO * g);
void Produci(GestioneIO * g, Buffer * b);
int Consuma(GestioneIO * g, Buffer * b);
