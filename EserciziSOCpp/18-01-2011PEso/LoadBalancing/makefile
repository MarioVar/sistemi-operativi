start: master.o procedure.o
	gcc -o start master.o procedure.o
master.o: master.c mex.h
	gcc -c master.c
procedure.o: procedure.c mex.h
	gcc -c procedure.c
clean:
	rm -f *.o
	rm -f ./start
