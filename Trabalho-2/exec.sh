#!/bin/bash
gcc -Wall -c data_structures.c -g
gcc -Wall -c functions.c -g
gcc -Wall -o main main.c data_structures.o functions.o -g