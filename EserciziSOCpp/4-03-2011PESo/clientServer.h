#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#define END -1
#define codaCS 1
#define N 100
pthread_mutex_t mutex;
int idcoda1;
int idcoda2;
typedef struct {
	long tipo;
	pid_t pid;
	int a;
	int b;
	int prodotto;
}messaggio;
typedef struct {
	int a;
	int b;
	pid_t pid;
}Dati;
void client(int fine);
void server();
