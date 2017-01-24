#include<pthread.h>
#define libero 0
#define in_uso 1
#define occupato 2
#define N 5
typedef struct{
	int cliente;
	int costo;
	int stato;
}acquisto;
typedef struct{
	acquisto vettore[N];
	int fatturato;
	int spazio_disp;
	pthread_mutex_t mutex;
	pthread_cond_t spazio_disponibile;
}MonitorNegozio;
extern MonitorNegozio* m;
void inizializza();
void rimuovi();
void inserisci_acquisto(int id_cliente,int costo);
void completa_acquisto(int id_cliente);
