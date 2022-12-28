#include"strutture.h"
#include"database.h"

//Aggiunge un utente ad una stanza. Ritorna 1 in caso di successo, 0 in caso di fallimento.
int addUserToRoom(PGconn *dbconn, stanza *room, utente *user)
{
    int max = room->numeroMaxGiocatori;
    int i;
    for(i = 0; i < max; i++) {
        if(room->players[i] == NULL){
            room->players[i] = user;
            db_insertUtenteToStanza(dbconn, room->idStanza, user->username);
            return 1;
        }
    }
    printf("Stanza piena!\n");
    return 0;
}

//Inserisce una nuova stanza nel db e inserisce l'utente admin nella stanza. Ritorna un puntatore alla nuova stanza, NULL per errori
stanza *crea_stanza(PGconn *dbconn, utente* admin, char nomeStanza[16], int numeroMax, int privato, char keyword[16])
{
    int idNuovaStanza = db_insertStanza(dbconn, admin->username, nomeStanza, numeroMax, privato, keyword);
    if(idNuovaStanza < 0)
        return NULL;
    stanza *nuovaStanza = new_stanza(idNuovaStanza, nomeStanza, numeroMax, privato, keyword, admin);
    addUserToRoom(dbconn, nuovaStanza, admin);
    return nuovaStanza;
}
