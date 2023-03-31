#!/bin/bash
gcc -o prova mainTest.c database.c strutture.c word.c -ljson-c -pthread -g -I/usr/include/postgresql -lpq
