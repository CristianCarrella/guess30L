#!/bin/bash
gcc -o prova Src/testDb.c testServer.c -I/usr/include/postgresql -lpq
