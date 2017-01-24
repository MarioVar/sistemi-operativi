lp=-pthread
all:start
start: main.c header.h procedure.c
	gcc $(lp) -o start main.c procedure.c
clean:
	rm -f *.o
	rm -f ./start
