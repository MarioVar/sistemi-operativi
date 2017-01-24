master: start server client

start: richiamo.o procedure.o
	gcc  -pthread -o start richiamo.o procedure.o

richiamo.o: richiamo.c header.h
	gcc -c richiamo.c

procedure.o: procedure.c header.h
	gcc -c procedure.c

client: client.c header.h
	gcc -pthread -o client client.c
server: server.c header.h
	gcc -pthread -o server server.c
clean:
	rm -f *.o
	rm -f ./client ./server ./start

