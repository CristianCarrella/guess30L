#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <json-c/json.h>
#include <time.h>
#include "strutture.h"

#define PORT 9876
#define MAX_CLIENTS 1
#define BUFFDIM 1024
#define NUMBER_OF_SUGGESTED_WORD 4

void start_game(stanza*);
void start_round(stanza*, int);
void prepareWords(char dest[BUFFDIM], char *parole[NUMBER_OF_SUGGESTED_WORD][2]);
void sendBroadcast(stanza* room, int idHost, char* msg);
struct json_object *generateHint(char *parola, int *hints);

#endif