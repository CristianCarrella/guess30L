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
#include "word.h"
#include <sys/time.h>

#define PORT 9876
#define MAX_CLIENTS 1
#define BUFFDIM 1024
#define NUMBER_OF_SUGGESTED_WORD 4

struct clientData
{
    int socket;
    stanza *room;
};

//Funzione da chiamare per cominciare la partita all'interno di una stanza. Ritorna l'username del vincitore della partita
char *start_room(stanza*, int);
// Ritorna l'index del vincitore all'interno dell'array players
int start_round(stanza*, int);
struct json_object *generateHint(char *parola, int *hints);
void sendBroadcast(stanza*, int, char*);
void prepareWords(char dest[BUFFDIM], char *parole[NUMBER_OF_SUGGESTED_WORD][2]);
int hintsIsFull(int *hints, int len);

#endif
