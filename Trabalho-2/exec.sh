#!/bin/bash
gcc -c data_structures.c
gcc -c functions.c
gcc -o main main.c data_structures.o functions.o