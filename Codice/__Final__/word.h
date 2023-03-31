#ifndef WORD_H
#define WORD_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include"database.h"

char* generateRandomWord();
void generateSuggestedWords(int numberOfWord, char* suggestedWord[numberOfWord][2]);
char* searchDefInDictionary(char* word);
void printSuggestedWords(int numberOfWord, char* suggestedWord[numberOfWord][2]);
#endif