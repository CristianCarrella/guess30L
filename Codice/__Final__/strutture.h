#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char username[32];
	char passw[16];
	char email[64];
	int partiteVinte;
	int idStanza;
} utente;

typedef struct {
	int idStanza;
	char nomeStanza[16];
	int numeroMaxGiocatori;
	int privato;
	char keyword[16];
	utente *adminUser;
	utente **players; //Array di utenti
	int *socket;
} stanza;

//Allocazione di un nuovo utente
utente *new_utente(char *name, char *pass, char *em, int wongames)
{
	utente *nuovo = (utente*)malloc(sizeof(utente));
	strcpy(nuovo->username, name);
	strcpy(nuovo->passw, pass);
	strcpy(nuovo->email, em);
	nuovo->partiteVinte = wongames;
	nuovo->idStanza = -1;
	return nuovo;
}

//Allocazione di una nuova stanza
stanza *new_stanza(int id, char* nome, int maxPlayer, int privat, char *kw, utente *admin)
{
	stanza *nuovo = (stanza*)malloc(sizeof(stanza));
	nuovo->idStanza = id;
	strcpy(nuovo->nomeStanza, nome);
	nuovo->numeroMaxGiocatori = maxPlayer;
	nuovo->privato = privat;
	strcpy(nuovo->keyword, kw);
	nuovo->adminUser = admin;
	nuovo->players = (utente**)malloc(maxPlayer*(sizeof(utente*)));
	for(int i = 0; i < maxPlayer; i++)
	{
		nuovo->players[i] = NULL;
	}
	nuovo->players[0] = admin;
	return nuovo;
}



/*

aggiungi utente
rimuovi utente

crea stanza
chiudi stanza

ricerca utenti
ricerca stanza

*/
