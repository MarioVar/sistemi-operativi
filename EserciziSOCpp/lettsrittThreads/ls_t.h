/*Lettori scrittori con thread e starvation degli scirttori*/
#include<pthread.h>
#define NUMTHREAD 10
#define N 5
#define letto 1
#define occupato 2
#define libero 3
/*struttura dati atta a contenere i messaggi*/
typedef struct{
	int numlettori;
	int buffer[N];
	int stato[N];
}Buffer;
Buffer b;
/*definizione mutex*/
pthread_mutex_t mutex;
/* definizione variabili condition*/
pthread_cond_t ok_lettura;
pthread_cond_t ok_scrittura;
/*firme funzioni*/
void * lettura(void * id);
void * scrittura(void* id);
