#define N_CONDS 2
#define OK_CONS 0
#define OK_PROD 1
#define N 5
#define libero 0
#define occupato 1
typedef struct {
	int msg_disp;
	int spazio_disp;
	int stato[N];
	int buffer[N];
}buffer;
void initBuffer(buffer*b);
int inizioProduzione(Monitor * m,buffer * b);
void fineProduzione(Monitor* m,buffer*b);
int inizioConsumo(Monitor * m,buffer *b);
void fineConsumo(Monitor* m,buffer*b);
void produzione(Monitor*m,buffer *b );
void consumo(Monitor *m,buffer *b);
