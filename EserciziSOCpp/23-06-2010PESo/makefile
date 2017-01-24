Match: partita.o procedure.o
	gcc -pthread -o Match procedure.o partita.o

partita.o: partita.c calcetto.h
	gcc -c partita.c
procedure.o: procedure.c calcetto.h
	gcc -c procedure.c
clean:
	rm -f *.o
	rm -f ./Match 
