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

stanza *stanze[50];
int stanze_lenght = 50;


//aggiungi utente					forse solo id
int add_user_in_room(utente *user, stanza *room){
	for (int i = 0; i < room->numeroMaxGiocatori; i++)
	{
		if(room->players[i] == NULL){
			user->idStanza = room->idStanza;
			room->players[i] = user;
			return 1;
		}
	}
	return 0;
}

//rimuovi utente !!!!!CONDRONTA I PUNTATORI!!!!!
int rm_user_from_room(utente *user, stanza *room ){
	for (int i = 0; i < room->numeroMaxGiocatori; i++)
	{
		if(room->players[i] != NULL){
			if(room->players[i] == user){
				user->idStanza = -1;
				room->players[i] = NULL;
				return 1;
			}
		}
	}

	return 0;
}

int add_stanza(char *name, int max_player, int priv, char *kw, utente *admin){
	for (int i = 0; i < stanze_lenght; i++)
	{
		if (stanze[i] == NULL)
		{
			stanze[i] = new_stanza(i, name, max_player, priv, kw, admin);
			return 1;
		}
	}
	return 0;
}

stanza *get_stanza_by_id(int id){
	if(id < stanze_lenght){
		if(stanze[id] != NULL){
			return stanze[id];
		}
	}
}

int rm_stanza_by_id(int id){
	if(id < stanze_lenght){
		if(stanze[id] != NULL){
			stanza *room = stanze[id];
			
			for (int i = 0; i < room->numeroMaxGiocatori; i++)
			{
				if(room->players[i] != NULL){
					room->players[i]->idStanza = -1;
				}
			}

			free(stanze[id]);
			stanze[id] = NULL;
		}
	}
}

int rm_stanza(stanza *room){
	rm_stanza_by_id(room->idStanza);
}

stanza *ricerca_stanza(stanza ** room, int idStanza){

}

void sort_stanza_by_id();

/*

aggiungi utente
rimuovi utente

crea stanza
chiudi stanza

ricerca utenti DB?
ricerca stanza

*/
