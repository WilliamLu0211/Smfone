all: control.o main.o
	gcc -o ctr control.o
	gcc -o main main.o

control.o: control.c x.h
	gcc -c control.c

main.o: main.c x.h
	gcc -c main.c

clean:
	rm *.o
