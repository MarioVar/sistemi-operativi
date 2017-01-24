#include<sys/types.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#define path0 "."
#define path1 "."
#define char0 'a'
#define char1 'b'
#define path3 "."
#define char3 'c'
#define mutex 1
#define ok_lettura 2
#define ok_scrittura 3
key_t key1,key2,key3;
#define N 5
typedef struct{
	int  m[N][N];
	int stop;
	int spazio;
	int nlettori;
	int nscrittori;
	int codalett;
	int codascritt;
	int msg;
}Gestore;
void inizializza(Gestore* g);
void genera(Gestore* g,int idsem);
void analizza(Gestore* g,int idsem);
void elabora(Gestore* g,int idsem);
