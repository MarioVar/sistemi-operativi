#define N 100
#define CLIENT 0
#define SERVER 1
#define nclient 8
#define nserver 3
#define nbalanc 1
#include <sys/types.h>
#include <sys/ipc.h>
int codaClient;
int codaBalancer;
typedef struct {
	long tipo;
	int pidC;
}messaggio;
void richiestaC();
void inoltroB();
void Server();


