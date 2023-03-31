#include"strutture.h"
utente *new_utente(char *name, char *pass, char *em, int wongames, int socket)
{
	utente *nuovo = (utente*)malloc(sizeof(utente));
	strcpy(nuovo->username, name);
	strcpy(nuovo->passw, pass);
	strcpy(nuovo->email, em);
	nuovo->partiteVinte = wongames;
	nuovo->idStanza = -1;
	return nuovo;
}

stanza *new_stanza(unsigned int id, char* nome, unsigned int maxPlayer, utente *admin)
{
	stanza *nuovo = (stanza*)malloc(sizeof(stanza));
	nuovo->idStanza = id;
	strcpy(nuovo->nomeStanza, nome);
	nuovo->numeroMaxGiocatori = maxPlayer;
	nuovo->started = false;
	nuovo->turn = 0;
	nuovo->adminUser = admin;
	nuovo->players = (utente**)malloc(maxPlayer*(sizeof(utente*)));
	for(int i = 0; i < maxPlayer; i++)
	{
		nuovo->players[i] = NULL;
	}
	nuovo->players[0] = admin;
	nuovo->numeroGiocatori = 1;
	return nuovo;
}


bool chooseStanza(utente* utente, unsigned int idStanza, head_q* stanze){
	struct node_s * e = NULL;
	stanza * stanzaScelta = NULL;
	TAILQ_FOREACH(e, stanze, nodes){
		if(e->stanza->idStanza == idStanza){
			stanzaScelta = e->stanza;
		}
	}
	if(stanzaScelta->numeroGiocatori == stanzaScelta->numeroMaxGiocatori){
		utente->idStanza = -1;
		printf("Sorry utente %s, room %d is full, (%d/%d)\n", utente->email, stanzaScelta->idStanza, stanzaScelta->numeroGiocatori, stanzaScelta->numeroMaxGiocatori);
		return false;
	}
	utente->idStanza = idStanza;
	addUtenteToStanza(utente, stanzaScelta);
	return true;
}

void addUtenteToStanza(utente* utente, stanza* stanza){
	stanza->players[stanza->numeroGiocatori] = utente;
	stanza->numeroGiocatori++;
	printf("Utente %s joined in room with id %d, (%d/%d)\n", utente->email, stanza->idStanza, stanza->numeroGiocatori, stanza->numeroMaxGiocatori);
}

void printUsers(head_t * head) {
    struct node_u * e = NULL;
    TAILQ_FOREACH(e, head, nodes)
    {
        printf("%s :: %d\n", e->utente->email, e->utente->idStanza);
    }
}

void printStanze(head_q * head) {
    struct node_s * e = NULL;
    TAILQ_FOREACH(e, head, nodes)
    {
        printf("\nUtenti presenti nella stanza %d:\n", e->stanza->idStanza);
		for(int i = 0; i < e->stanza->numeroGiocatori; i++){
			printf("userid[%d] = %s\n", i, e->stanza->players[i]->email);
		}
    }
}

void addToListUtente(head_t* head, utente* utente) {
	struct node_u * e = malloc(sizeof(struct node_u));
	if (e == NULL)
	{
		fprintf(stderr, "malloc failed");
		exit(EXIT_FAILURE);
	}
	e->utente = utente;
	TAILQ_INSERT_TAIL(head, e, nodes);
	e = NULL;
}

void addToListStanza(head_q* head, stanza* stanza) {
	struct node_s * e = malloc(sizeof(struct node_s));
	if (e == NULL)
	{
		fprintf(stderr, "malloc failed");
		exit(EXIT_FAILURE);
	}
	e->stanza = stanza;
	TAILQ_INSERT_TAIL(head, e, nodes);
	e = NULL;
}

void printUtente(utente* utente){
	printf("Welcome: %s\n", utente->email);
}