#ifndef STRUTTURE_H
#define STRUTTURE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<sys/queue.h>
#include <pthread.h>

typedef struct {
	char username[32];
	char passw[16];
	char email[64];
	int partiteVinte;
	int idStanza;
	int socket;
	int imgid;
} utente;

typedef struct {
	unsigned int idStanza;
	char nomeStanza[16];
	unsigned int numeroMaxGiocatori;
	unsigned int numeroGiocatori;
	utente *adminUser;
	utente **players; //Array di utenti
	unsigned int turn;
	bool started;
} stanza;

typedef struct node_u
{
    utente* utente;
    TAILQ_ENTRY(node_u) nodes;
} node_j;
typedef TAILQ_HEAD(head_u, node_u) head_t;


typedef struct node_s
{
    stanza* stanza;
    TAILQ_ENTRY(node_s) nodes;
} node_t;
typedef TAILQ_HEAD(head_s, node_s) head_q;


utente *new_utente(char *name, char *pass, char *em, int wongames, int socket, int imgid);
stanza *new_stanza(unsigned int id, char* nome, unsigned int maxPlayer, utente *admin);
void printStanze(head_q* head);
void printUsers(head_t* head);
bool chooseStanza(utente *utente, unsigned int idStanza, head_q* stanze);
void addToListUtente(head_t* head, utente* utente);
void addToListStanza(head_q* head, stanza* stanza);
void printUtente(utente* utente);
void addUtenteToStanza(utente* utente, stanza* stanza);

#endif