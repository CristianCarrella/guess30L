#ifndef STRUTTURE_H
#define STRUTTURE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
	char username[32];
	char passw[16];
	char email[64];
	int partiteVinte;
	int idStanza;
	int clientSocket;
} utente;

typedef struct {
	int idStanza;
	char nomeStanza[16];
	int numeroMaxGiocatori;
	int numeroGiocatori;
	int turn;
	bool started;
	utente *adminUser;
	utente **players; //Array di utenti
} stanza;

//Allocazione di un nuovo utente
utente *new_utente(char *name, char *pass, char *em, int wongames);

//Allocazione di una nuova stanza
stanza *new_stanza(int id, char* nome, int maxPlayer, utente *admin);

int rm_stanza_by_id(int id);

int rm_stanza(stanza *room);

//aggiungi utente					forse solo id
int add_user_in_room(utente *user, stanza *room);

//rimuovi utente !!!!!CONDRONTA I PUNTATORI!!!!!
int rm_user_from_room(utente *user, stanza *room );

int add_stanza(char *name, int max_player, char *kw, utente *admin);

stanza *get_stanza_by_id(int id);

#include "strutture.c"

#endif
