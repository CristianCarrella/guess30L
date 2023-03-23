#include "strutture.h"

int main(){
	//utente *new_utente(char *name, char *pass, char *em, int wongames)
	utente *utente1 = new_utente("cio", "cjie", "hfbuwi", 0);
	stanza *stanza1 = new_stanza(1, "ciao",9, 1,"ff" , utente1);
	stanza1->players[1] = new_utente("cio", "cjie", "hfbuwi", 0);
	printf("%d" , stanza1->players[0]->idStanza);
}