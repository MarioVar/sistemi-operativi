mon= ../monitor/monitor.o
all:start
start: main.c header.h procedure.c
	gcc -o start main.c procedure.c $(mon)
clean:
	rm -f *.o
	rm -f ./start
