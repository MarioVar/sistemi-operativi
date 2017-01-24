

#define NUM_CONDITIONS 2
#define SYNC_L 0
#define SYNC_S 1
			/*lettori scrittori con starvation lettori*/
typedef long msg;


typedef struct {
	msg messaggio;
	int numlettori;
	int occupato;
}memory;

void iniziolettura(memory*,Monitor*);
void inizioscrittura(memory*,Monitor*);

void finelettura(Monitor*,memory* mem);
void finescrittura(Monitor*,memory* mem);

void Produzione(memory*,Monitor*);
void Lettura(memory*,Monitor*);



