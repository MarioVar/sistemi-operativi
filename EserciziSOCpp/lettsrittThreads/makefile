all: start
start: ls_t.o procedure.o
	gcc -pthread -o start ls_t.o procedure.o

procedure.o: procedure.c ls_t.h
	gcc -c procedure.c
ls_t.o: ls_t.c ls_t.h
	gcc -c ls_t.c
clean:
	rm -f *.o
	rm -f ./start
