pathM=../monitor/monitor.o
prodcons: prodcons.o procedure.o
	gcc -o prodcons prodcons.o procedure.o $(pathM)
prodcons.o: prodcons.c prodcons.h
	gcc -c prodcons.c
procedure.o: procedure.c prodcons.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f ./prodcons
