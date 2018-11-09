#!/bin/bash
gcc -c data_structures.c -g
gcc -c functions.c -g
gcc -o main main.c data_structures.o functions.o -g