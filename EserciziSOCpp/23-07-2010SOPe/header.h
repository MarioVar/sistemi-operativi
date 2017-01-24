#define BUFFER 1
#define PRINTER 2

typedef struct{
	long tipo;
	int idClient;
}messaggio;
void server(int bid,int idp);
void client(int bid);
void printer(int idp);
