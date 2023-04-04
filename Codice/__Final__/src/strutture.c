#ifndef STRUTTURE_C
#define STRUTTURE_C

#include "../header/strutture.h"

stanza *stanze[50];
int stanze_lenght = 50;

//Allocazione di un nuovo utente
utente *new_utente(char *name, char *pass, char *em, int wongames, int socket, int imgid)
{
	utente *nuovo = (utente*)malloc(sizeof(utente));
	strcpy(nuovo->username, name);
	strcpy(nuovo->passw, pass);
	strcpy(nuovo->email, em);
	nuovo->partiteVinte = wongames;
	nuovo->idStanza = -1;
	nuovo->clientSocket = socket;
	nuovo->imgId = imgid;
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
\

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

int add_user_in_room_by_id(utente *user, int id){
	add_user_in_room(user,get_stanza_by_id(id));
}


//rimuovi utente !!!!!CONDRONTA I PUNTATORI!!!!!
int rm_user_from_room(utente *user, stanza *room ){
	// strcmp non worka strcmp(room->adminUser->username,user->username)
	printf("\nl admin è %s mentre l utente trovato è %s\n", room->adminUser->username, user->username);
	if(room->adminUser == user){
		rm_stanza(room);
	}
	else for (int i = 0; i < room->numeroMaxGiocatori; i++)
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

int add_stanza(char *name, int max_player, char *kw, utente *admin){
	for (int i = 0; i < stanze_lenght; i++)
	{
		if (stanze[i] == NULL)
		{
			stanze[i] = new_stanza(i, name, max_player, admin);
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

#endif

// stanza *ricerca_stanza(stanza ** room, int idStanza);

// void sort_stanza_by_id();
