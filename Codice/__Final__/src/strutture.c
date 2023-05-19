#ifndef STRUTTURE_C
#define STRUTTURE_C

#include "../header/strutture.h"

stanza *stanze[50];
int stanze_lenght = 50;

pthread_mutex_t mutex;
pthread_cond_t condition;

//Allocazione di un nuovo utente
utente *new_utente(char *name, char *pass, char *em, int wongames, int socket, int imgid, pthread_t tid)
{
	utente *nuovo = (utente*)malloc(sizeof(utente));
	strcpy(nuovo->username, name);
	strcpy(nuovo->passw, pass);
	strcpy(nuovo->email, em);
	nuovo->partiteVinte = wongames;
	nuovo->idStanza = -1;
	nuovo->clientSocket = socket;
	nuovo->imgId = imgid;
	nuovo->tid = tid;
	return nuovo;
}

//Allocazione di una nuova stanza
stanza *new_stanza(int id, char* nome, int maxPlayer, utente *admin)
{
	stanza *nuovo = (stanza*)malloc(sizeof(stanza));
	nuovo->idStanza = id;
	strcpy(nuovo->nomeStanza, nome);
	nuovo->numeroMaxGiocatori = maxPlayer;
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


int rm_stanza_by_id(int id){
	int success = false;
	if(id < stanze_lenght){
		printf("arrivo al semaforo rm_stanza");
		//acquisizione
		pthread_mutex_lock(&mutex);
		// pthread_cond_wait(&condition, &mutex);

		if(stanze[id] != NULL){
			success = true;
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

		pthread_mutex_unlock(&mutex);

	}
	return success;
}

int rm_stanza(stanza *room){
	return rm_stanza_by_id(room->idStanza);
}

//aggiungi utente					forse solo id
int add_user_in_room(utente *user, stanza *room){
	if(user == NULL || room == NULL){
		return false;
	}
	int success = false;
	//acquisizione
	pthread_mutex_lock(&mutex);
	int tmp = -1;
	for (int i = 0; i < room->numeroMaxGiocatori; i++){
		if(room->players[i] != NULL ){
			if(room->players[i] == user){
				success = true;
				break;
			}
		}else if(tmp == -1){
			tmp = i;
		}
	}
	if(tmp != -1){
		user->idStanza = room->idStanza;
		room->players[tmp] = user;
		success = true;
	}

	// room = NULL;
	pthread_mutex_unlock(&mutex);

	return success;
}

int add_user_in_room_by_id(utente *user, int id){
	add_user_in_room(user,get_stanza_by_id(id));
}


//rimuovi utente !!!!!CONDRONTA I PUNTATORI!!!!!
int rm_user_from_room(utente *user, stanza *room ){
	int success;
	if(user == NULL || room == NULL){
		printf("user o stanza NULL ");
		if(user == NULL){
			printf("user NULL ");
		}
		if(room == NULL){
			printf("stanza NULL ");
		}
		success = false;
	}
	// strcmp non worka strcmp(room->adminUser->username,user->username)
	printf("\nl admin è %s mentre l utente trovato è %s\n", room->adminUser->username, user->username);
	if(room->adminUser == user){
		success = rm_stanza(room);
	}
	else for (int i = 0; i < room->numeroMaxGiocatori; i++){
		if(room->players[i] != NULL){
			if(room->players[i] == user){
				user->idStanza = -1;
				room->players[i] = NULL;
				success = true;
				break;
			}
		}
	}
	return false;
}

int add_stanza(char *name, int max_player, utente *admin){
	int id = 0;
	pthread_mutex_lock(&mutex);
	//pthread_cond_wait(&condition, &mutex);
	for (int i = 0; i < stanze_lenght; i++)
	{
		if (stanze[i] == NULL)
		{
			stanze[i] = new_stanza(i, name, max_player, admin);
			id = i;
			admin->idStanza = id;
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
	return id;
}

stanza *get_stanza_by_id(int id){
	if(id < stanze_lenght){
		if(stanze[id] != NULL){
			return stanze[id];
		}
	}
}

stanza* get_stanze(){
	//FUNZIONE PER OTTENERE TUTTE LE STANZE DISPONIBILI
	stanza *stanze;
	return stanze;
}

void visualizza_stanze(){
	for (int i = 0; i < stanze_lenght; i++)
	{
		if(stanze[i] != NULL){
			printf("nome: %s, id: %d\n", stanze[i]->nomeStanza, stanze[i]->idStanza);
			for (int j = 0; j < stanze[i]->numeroMaxGiocatori; j++)
			{
				if(stanze[i]->players[j] != NULL){
					printf("-->%s\n", stanze[i]->players[j]->username);
				}
			}
		}
	}
}

#endif

//se un utente entra in una nuova stanza deve uscire dalla stanza attuale