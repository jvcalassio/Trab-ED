all: main

main: main.c data_structures.o functions.o
	gcc -ansi -o main main.c data_structures.o functions.o -g

functions.o: functions.c functions.h
	gcc -ansi -c functions.c -g

data_structures.o: data_structures.c data_structures.h
	gcc -ansi -c data_structures.c -g

clean:
	rm -rf *.o *~ main