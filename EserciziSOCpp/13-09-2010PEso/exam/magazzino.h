#define numproc 20
#define N 100
#define libero 0
#define occupato 1
#define in_uso 2
#define SPAZIODISP 0
#define PRODDISP 1
typedef struct{
	unsigned int id_fornitore;
	unsigned int stato;
}scaffale;
int livello_scorte;
int iniziofornitura(Monitor* m, scaffale *s);
void finefornitura(Monitor * m);
void fornitura(Monitor*m,scaffale *s);
int inizioacquisto(Monitor *m, scaffale *s);
void fineacquisto(Monitor *m);
void acquisto(Monitor*m,scaffale* s);
