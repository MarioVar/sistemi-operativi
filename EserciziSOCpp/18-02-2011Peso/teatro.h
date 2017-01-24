#define libero 0
#define POSTI_DISP 80
#define occupato 1
#define in_aggiornamento 2
#define cond_ok_pren 3
#define mutex 4
#define PATH "."
#define CHAR 'a'
#define PATH2 "."
#define CHAR2 'b'
#include <sys/types.h>
#include <sys/ipc.h>
typedef struct {
unsigned int idCliente; /*id_cliente è il PID del cliente che ha prenotato il posto (inizialmente 0)*/
unsigned int stato; /*stato indica se il posto è libero (0), occupato (1), o in_aggiornamento (2) da parte di un altro cliente*/
} posto;
int disponibilita; //posti attualmente disponibili(inizialmente 80)

/*FIRME FUNZIONI*/
void prenotazione(posto * p);
void bacheca(posto * p);
