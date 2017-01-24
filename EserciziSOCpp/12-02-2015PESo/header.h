#include<pthread.h>
#define OCCUPATO 0
#define IN_USO 1
#define LIBERO 2
#define ESEGUITO 3
#define N 5
typedef struct {
	int operandi[4]; // il buffer contiene un array di operandi (da 2 a 4)
	int totale_operandi; // il numero di operandi presenti nell'array
} buffer;
typedef struct {
	buffer elaborazioni[N];
	int stato[N];
	int elem_disp;
	pthread_mutex_t	mutex;
	pthread_cond_t ok_prod;
	pthread_cond_t ok_cons;
} MonitorElaborazioni;
void Inizializza(MonitorElaborazioni * m);
void inserisci_buffer(MonitorElaborazioni* m,int operandi);
void preleva_buffer(MonitorElaborazioni* m);
void Rimuovi(MonitorElaborazioni * m);
