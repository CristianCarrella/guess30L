#include "strutture.h"

//Allocazione di un nuovo utente
utente *new_utente(char *name, char *pass, char *em, int sock, int wongames)
{
	utente *nuovo = (utente*)malloc(sizeof(utente));
	strcpy(nuovo->username, name);
	strcpy(nuovo->passw, pass);
	strcpy(nuovo->email, em);
    nuovo->clientSocket = sock;
	nuovo->partiteVinte = wongames;
	nuovo->idStanza = -1;
	return nuovo;
}

//Allocazione di una nuova stanza
stanza *new_stanza(int id, char* nome, int maxPlayer, utente *admin)
{
	stanza *nuovo = (stanza*)malloc(sizeof(stanza));
	nuovo->idStanza = id;
	strcpy(nuovo->nomeStanza, nome);
	nuovo->numeroMaxGiocatori = maxPlayer;
    nuovo->numeroGiocatori = 1;
    nuovo->turn = 0;
    nuovo->started = false;
	nuovo->adminUser = admin;
	nuovo->players = (utente**)malloc(maxPlayer*(sizeof(utente*)));
	for(int i = 0; i < maxPlayer; i++)
	{
		nuovo->players[i] = NULL;
	}
	nuovo->players[0] = admin;
	return nuovo;
}