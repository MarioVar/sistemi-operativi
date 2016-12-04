PATHM=../monitor/monitor.o

exam1: magazzino.o procedure.o
	gcc -DEBG -o exam1 magazzino.o procedure.o $(PATHM)
magazzino.o: magazzino.c magazzino.h 
	gcc -c magazzino.c
procedure.o: procedure.c magazzino.h
	gcc -c procedure.c
clean:
	rm -f *.o
	rm -f ./exam1
