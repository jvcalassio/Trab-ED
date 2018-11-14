all: main

main: main.c data_structures.o functions.o
	gcc -o main main.c data_structures.o functions.o -g

functions.o: functions.c functions.h
	gcc -c functions.c -g

data_structures.o: data_structures.c data_structures.h
	gcc -c data_structures.c -g

clean:
	rm -rf *.o *~ main