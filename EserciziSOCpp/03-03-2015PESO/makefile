all: p1 p2 p2 principale
principale: main.c procedure.c header.h
	gcc -o principale main.c procedure.c
p1: P1.c header.h procedure.c
	gcc -o P1 P1.c procedure.c
p2: P2.c header.h procedure.c
	gcc -o P2 P2.c procedure.c
p3: P3.c header.h procedure.c
	gcc -o P3 P3.c procedure.c
clean:
	rm -f *.o
	rm -f ./P1 ./P2 ./P3 ./principale
