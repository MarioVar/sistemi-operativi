master: produttore consumatore
	gcc -o master master.c

produttore: produttore.c esercitazione.h
	gcc -o produttore produttore.c procedure.c -lm

consumatore: consumatore.c esercitazione.h
	gcc -o consumatore consumatore.c procedure.c -lm

clean:
	rm -f *.o
	rm -f ./consumatore ./produttore ./master
