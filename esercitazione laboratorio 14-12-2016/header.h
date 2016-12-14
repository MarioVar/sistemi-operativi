#include<pthread.h>
#define N 3
#define libero 1
#define in_uso 2
#define occupato 3
typedef struct{
	int id;
	int quota;
}volo;
typedef struct{
	volo vettore[N];
	int stato[N];
	int spazio;
	pthread_mutex_t mutex;
	pthread_cond_t spazio_disp;
}gestorevolo;
extern gestorevolo* g;
void aggiungi_volo(gestorevolo* g,int id);
void rimuovi_volo(gestorevolo*g,int id);
void aggiorna_quota(gestorevolo *g, int id,int nuovaquota);
