#!/bin/bash
gcc -o server serverTest.c database.c strutture.c word.c -ljson-c -pthread -g -I/usr/include/postgresql -lpq
gcc -o client clientTest.c -ljson-c
