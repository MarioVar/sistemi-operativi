MNTLIB=../monitor/monitor.o
all:start

start:  main.o procedure.o
	gcc -o start main.o procedure.o $(MNTLIB)

main.o: main.c ls.h
	gcc -c main.c

procedure.o: procedure.c ls.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f ./start
