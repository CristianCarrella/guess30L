#include "../header/gameManager.h"
#include "../header/word.h"

void start_game(stanza* currentRoom) {
    //per ogni turno: la funzione manda la stringa "starting" a tutti tranne a chi deve scegliere la parola che invece riceverà "choose" seguito dalle 5 possibili parole
    // il server aspetterà di ricevere la parola scelta e la manderà a tutti gli altri
    // iniziando dal primo giocatore il server [attiva un timer e] si mette in attesa di sapere se la parola è stata indovinata
    // se la parola è stata indovinata lo comunica a tutti gli altri giocatori e si riparte, altrimenti si passa al prossimo giocatore
    // una volta che tutti hanno provato il sever comunica che è finito il giro, manda una lettera casuale come indizio e il giro riparte
    currentRoom->started = true;
    int i;
    
    //for(i = 0; i < currentRoom->numeroMaxGiocatori; i++){
        //if(currentRoom->players[i] == NULL)
            //continue;
        start_round(currentRoom, i);
    //}
}

void start_round(stanza *room, int idPlayer) {
    int i = 0;
    char buffer[BUFFDIM];
    char *parole[NUMBER_OF_SUGGESTED_WORD][2];

    generateSuggestedWords(NUMBER_OF_SUGGESTED_WORD, parole);
    prepareWords(buffer, parole);
    printf("%s", buffer);

    for(i = 0; i < room->numeroMaxGiocatori; i++) {
        if(room->players[i] == NULL)
            continue;
        else if(idPlayer == i) {
            send(room->players[idPlayer]->clientSocket, buffer, strlen(buffer), 0);
        }
        else {
            send(room->players[i]->clientSocket, "Starting...\n", strlen(buffer), 0);
        }
    }
}

void prepareWords(char dest[BUFFDIM], char *parole[NUMBER_OF_SUGGESTED_WORD][2]){
    int i;
    //sprintf(dest, "");
    for(i = 0; i < NUMBER_OF_SUGGESTED_WORD; i++){
        strcat(dest, parole[i][0]);
        strcat(dest, ": ");
        strcat(dest, parole[i][1]);
        strcat(dest, "\n");
    }
}