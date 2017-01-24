#define Nthread 12
#define TEAM_A 1
#define TEAM_B 2
#include<pthread.h>
typedef struct {
unsigned int goal_A;
unsigned int goal_B;
pthread_mutex_t mutex;
pthread_cond_t ok_lettura;
pthread_cond_t ok_scrittura;
int occupato_da_scrittore;
int nlettori;
} partita;
void lettura(partita * p);
void aggiorna_risultato(partita * p,int goal,int seleziona);
