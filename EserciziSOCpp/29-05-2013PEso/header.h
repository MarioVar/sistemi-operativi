#include<pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#define char1 'a'
#define char2 'b'
#define path1 "."
#define path2 "."
#define N 100
#define END -1
#define occupato 0
#define libero 1
key_t key1,key2;
pthread_t manager,worker[2];
pthread_mutex_t mutex;
int coda_richiesta;
int coda_risposta;
typedef struct{
	long tipo;
	pid_t pid;
	int a;
	int b;
	int prodotto;
	int stato;
}messaggio;
size_t bytercv;
void client(int endnow);
void server();
