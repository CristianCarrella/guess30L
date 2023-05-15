#include "../header/gameManager.h"

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

void start_round(stanza *room, int idHostPlayer) {
    int i = 0, j = 0;
    char choosenWord[32];
    char buffer[BUFFDIM];
    char *parole[NUMBER_OF_SUGGESTED_WORD][2];
    int choosenWordIndex;

    //Selezione parola da parte dell'host del round
    generateSuggestedWords(NUMBER_OF_SUGGESTED_WORD, parole);
    prepareWords(buffer, parole);
    printf("%s", buffer);
    send(room->players[idHostPlayer]->clientSocket, buffer, strlen(buffer), 0); //Invio delle parole suggerite
    memset(buffer, 0, sizeof(buffer));
    recv(room->players[idHostPlayer]->clientSocket, buffer, 32, 0 ); //In attesa di ricevere la parola scelta
    while(strcmp(parole[choosenWordIndex][0], buffer) != 0){ //Estrazione dell'indice della parola scelta dalla matrice
        choosenWordIndex++;
    }
    strcpy(choosenWord, parole[choosenWordIndex][0]);
    printf("La parola scelta è %s\n - %s\n", choosenWord, parole[choosenWordIndex][1]);

    //Invio della parola scelta + definizione ai giocatori
    struct json_object *jsObj = json_object_new_object();
    json_object_object_add(jsObj, "word", json_object_new_string(choosenWord));
    json_object_object_add(jsObj, "definition", json_object_new_string(parole[choosenWordIndex][1]));
    sendBroadcast(room, idHostPlayer, json_object_to_json_string(jsObj));

    int guessed = 0;
    int *hints = (int*)calloc(strlen(choosenWord), sizeof(int));
    do {
        for(i = 0; i < room->numeroMaxGiocatori; i++) {
            if(room->players[i] == NULL || i == idHostPlayer)
                continue;
            else {
                send(room->players[i]->clientSocket, "YOUR TURN", 10, 0);
                memset(buffer, 0, sizeof(buffer));
                recv(room->players[i]->clientSocket, buffer, BUFFDIM, 0);
                printf("%s\n", buffer);
                sendBroadcast(room, i, buffer);
                struct json_object *jsObj = json_tokener_parse(buffer);
                guessed = json_object_get_boolean(json_object_object_get(jsObj, "guessed"));
                if(guessed) {
                    break;
                }
            }
        }
        sendBroadcast(room, -1, "NEW HINT");
        struct json_object *js_hint = generateHint(choosenWord, hints);
        sendBroadcast(room, -1, json_object_to_json_string(js_hint));
    } while(!guessed);
    free(hints);
    //Deallocare json object
}

void sendBroadcast(stanza* room, int idHost, char* msg) {
    int i;
    char response[BUFFDIM];
    memset(response, 0, sizeof(response));
    for(i = 0; i < room->numeroMaxGiocatori; i++){
        if(room->players[i] == NULL || i == idHost)
            continue;
        else {
            send(room->players[i]->clientSocket, msg, strlen(msg), 0);
            printf("waiting response from sock %d ... ", room->players[i]->clientSocket);
            recv(room->players[i]->clientSocket, response, BUFFDIM, 0);
            printf("%s\n", response);
        }   
    }
}

struct json_object *generateHint(char *parola, int *hints) {
    time_t t;
    srand((unsigned) time(&t));
    
    char c[1];
    int len = strlen(parola), position;
    do {
        position = rand()%len;
    } while(hints[position] == 1);
    hints[position] = 1;
    c[0] = parola[position];

    struct json_object *jsObj = json_object_new_object();
    json_object_object_add(jsObj, "letter", json_object_new_string(c));
    json_object_object_add(jsObj, "position", json_object_new_int(position));
    return jsObj;
}

void prepareWords(char dest[BUFFDIM], char *parole[NUMBER_OF_SUGGESTED_WORD][2]){
    int i;
    sprintf(dest, "");
    for(i = 0; i < NUMBER_OF_SUGGESTED_WORD; i++){
        strcat(dest, parole[i][0]);
        strcat(dest, ": ");
        strcat(dest, parole[i][1]);
        strcat(dest, "\n");
    }
}
