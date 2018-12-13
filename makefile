all : control.o main.o
	gcc -o ctrl control.o
	gcc -o write main.o

control.o: control.c
	gcc -c control.c

main.o: main.c
	gcc -c main.c

clean:
	rm -rf *.o

	
