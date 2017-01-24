provadeltre: main.o procedure.o
	gcc -pthread -o provadeltre procedure.o main.o
main.o: main.c clientServer.h
	gcc -c main.c
procedure.o: procedure.c clientServer.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f ./provadeltre
