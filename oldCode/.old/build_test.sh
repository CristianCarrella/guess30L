#!/bin/bash
gcc -o prova testing/dbtest.c database.c strutture.c word.c base64.c  mainTest.c -ljson-c -pthread -g -I/usr/include/postgresql -lpq
