#include "strutture.h"

void menu(){
	printf("inserisci nickname ");
	char nick[30];
	scanf("%s", nick);
	printf("%s", nick);
	utente *me = new_utente(nick, nick, nick, -1);

	printf("inserisci nome stanza ");
	char sTmp[30];
	scanf("%s", sTmp);
	printf("inserisci n max player ");
	int intTmp;
	scanf("%d", &intTmp);
	add_stanza(sTmp, intTmp,0,"Menu",me);
while(1){
	printf("cosa vuoi fare?\npremi 0 per uscire dalla stanza id\nPremi 1 per aggiungere un altro player alla stanza id\npremi 2 per creare un altra stanza\npremi 3 per rimuovere la stanza id\n");
	scanf("%d", &intTmp);

	switch (intTmp)
	{
	case 0:
		printf("inserisci id");
		scanf("%d", &intTmp);
		rm_user_from_room(me,get_stanza_by_id(intTmp));
		break;
	case 1:
		char temp[30];
		printf("dammi l username");
		scanf("%s", &temp);
		printf("dammi l id della stanza");
		scanf("%d", &intTmp);
		add_user_in_room(new_utente(temp,temp,temp,0), get_stanza_by_id(intTmp));
		break;
	default:
		break;
	}
}
}

void visualizza_stanze(){
	for (int i = 0; i < stanze_lenght; i++)
	{
		ulong
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








//Codice per test
int main(){
	menu();

	add_stanza("mia",6,0,"kk",new_utente("admin", "cjie", "hfbuwi", 0));
	//utente *new_utente(char *name, char *pass, char *em, int wongames);
	stanza *stanza1 = get_stanza_by_id(0);
	utente *utente1 = new_utente("gufo", "gufo", "gufo", 0);
	add_user_in_room(utente1, stanza1);
	add_user_in_room(new_utente("gufo1", "gufo1", "gufo1", 0),stanza1);
	add_user_in_room(new_utente("gufo11", "gufo11", "gufo11", 0),stanza1);
	rm_user_from_room(utente1, stanza1);
	visualizza_stanze();
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

