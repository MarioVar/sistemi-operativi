TH=-pthread
all:start
start: main.c procedure.c header.h
	gcc $(TH) -o start procedure.c main.c
clean:
	rm -f *.o
	rm ./start
