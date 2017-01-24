
master: start visualizzatore
	

start: procedure.o main.o 
	gcc -o start procedure.o main.o

procedure.o: procedure.c teatro.h
	gcc -c procedure.c

main.o: main.c teatro.h
	gcc -c main.c

visualizzatore: visualizzatore.c teatro.h
	gcc -o visualizzatore visualizzatore.c procedure.c

clean:
	rm -f *.o
	rm -f ./start ./bacheca
