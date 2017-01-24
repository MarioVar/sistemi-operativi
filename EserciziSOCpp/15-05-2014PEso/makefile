pizzaefigliTelecom: procedure.o pizzeria.o
	gcc -pthread -o pizzaefigliTelecom pizzeria.o procedure.o
pizzeria.o: pizzeria.c pizzeria.h
	gcc -c pizzeria.c
procedure.o: procedure.c pizzeria.h
	gcc -c procedure.c

clean:
	rm -f *.o
	rm -f ./pizzaefigliTelecom
