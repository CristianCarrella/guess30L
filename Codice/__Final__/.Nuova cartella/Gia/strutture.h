#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char username[32];
	char passw[16];
	char email[64];
    int clientSocket;
	int partiteVinte;
	int idStanza;
} utente;

typedef struct{
	int idStanza;
	char nomeStanza[16];
	int numeroMaxGiocatori;
    int numeroGiocatori;
    int turn;
    bool started;
	utente *adminUser;
	utente **players; //Array di utenti
} stanza;

utente *new_utente(char *name, char *pass, char *em, int sock, int wongames);
stanza *new_stanza(int id, char* nome, int maxPlayer, utente *admin);