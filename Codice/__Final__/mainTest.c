#include "strutture.h"

int main(){
	add_stanza("mia",6,0,"kk",new_utente("admin", "cjie", "hfbuwi", 0));
	//utente *new_utente(char *name, char *pass, char *em, int wongames);
	stanza *stanza1 = get_stanza_by_id(0);
	utente *utente1 = new_utente("gufo", "gufo", "gufo", 0);
	add_user_in_room(utente1, stanza1);
	add_user_in_room(new_utente("gufo1", "gufo1", "gufo1", 0),stanza1);
	add_user_in_room(new_utente("gufo11", "gufo11", "gufo11", 0),stanza1);
	rm_user_from_room(utente1, stanza1);

	rm_stanza(stanza1);

	// for (int i = 0; i < stanza1->numeroMaxGiocatori; i++)
	// {
	// 	if (stanza1->players[i] != NULL)
	// 	{
	// 		char temp[32];
	// 		strcpy(temp, stanza1->players[i]->username);
	// 		printf("il %d è",i);
	// 		for (int j = 0; j < 32; j++)
	// 		{
	// 			printf("%c", temp[j]);
	// 		}
	// 		printf("\n");
	// 	}
	// }


	if (1){
		printf("TRUE");
	}

}