#define N 4
#define PIZZEDISP 2
#define MARGHERITA 1
#define CALZONE 2
#define VUOTO 0 
#define PRONTO 1
#define IN_CONSEGNA 2
#include<pthread.h>
struct consegna{
	int pizza;
	int stato;
	int cliente;
};
struct Monitor{
	struct consegna c[5];
	pthread_mutex_t mutex;
	pthread_cond_t ok_nuova_consegna;
	pthread_cond_t ok_spazio_consegne;
	int nOrdini;
};
void aggiungi_consegna(struct Monitor * m,int pizza,int cliente);
int inizia_consegna(struct Monitor * m);
void fine_consegna(struct Monitor * m, int indice_consegna);
