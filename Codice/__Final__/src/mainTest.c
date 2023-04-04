#include "word.h"
#include "main.h"
#include "testing/dbtest.h"
// sudo apt install libjson-c-dev
#include <json-c/json.h>


void checkConnectionToDb(PGconn *conn){
	if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        PQfinish(conn);
    }else{
		printf("Successful connected to database [V]\n");
	}
}

head_q stanze;
unsigned int idStanze = 0;
unsigned int idUser = 0;
pthread_mutex_t mutex;

void *handle_client(void *socket_) {
	// int socket = *(int*) socket_;
	pthread_mutex_lock(&mutex);
	char buf[25];
	snprintf(buf, 12, "utente%d", idUser);
	utente* utente = new_utente(buf, "pass", strcat(buf, "@email.com"), 10, idUser, 0);
	idUser++;
	
	chooseStanza(utente, 0, &stanze);
	// printUtente(utente);
	pthread_mutex_unlock(&mutex);
}

/*TEST MAIN*/
int main(){

	/*CONNESSIONE AL DB - LOGIN - REGISTRAZIONE - UPDATE PARTITE*/
	PGconn *conn = PQconnectdb("postgresql://user:admin@localhost:54320/postgres"); //docker inspect -f '{{range.NetworkSettings.Networks}}{{.IPAddress}}{{end}}' container_name_or_id
	// checkConnectionToDb(conn);
	// signupTest(conn);
	// loginTestUserExist(conn, -1);
	// loginTestUserNotExist(conn, -1);
	// updatePartiteVinteTest(conn, -1);
	char email[64] = "provae";
	setAvatarOfUser(conn, email, 1);
	getAvatarByEmail(conn, email);
	

	/*GENERAZIONE DELLE PAROLE*/
	// unsigned int const NUMBER_OF_SUGGEST_WORD = 5;
	// char *words[NUMBER_OF_SUGGEST_WORD][2];
	// generateSuggestedWords(NUMBER_OF_SUGGEST_WORD, words);
	// printSuggestedWords(NUMBER_OF_SUGGEST_WORD, words);

	/*SCELTA DELLA STANZA*/
	// unsigned int const NUM_OF_UTENTI = 10;
	// unsigned int const NUM_OF_STANZE = 5;
	// pthread_t thread_id[NUM_OF_UTENTI];
	// TAILQ_INIT(&stanze);
	// int socket = 0;
	// //CREO UN UTENTE NELLA STANZA 0
	// utente* utente = new_utente("utente", "pass", "ema", 10, socket);
	// idUser++;
	// addToListStanza(&stanze, new_stanza(idStanze++, "stanza", 6, utente));
	// // SIMULO LA CONCORRENZA DI NUM_OF_UTENTI UTENTI CHE SCELGONO L'UNICA STANZA CON IDSTANZA = 0
	// if (pthread_mutex_init(&mutex, NULL) != 0)
    // {
    //     printf("\n mutex init failed\n");
    //     return 1;
    // }

	// for(int i = 0; i < NUM_OF_UTENTI; i++){
	// 	if (pthread_create(&thread_id[i], NULL, &handle_client, NULL) < 0) {
    //         perror("pthread_create failed");
    //         exit(EXIT_FAILURE);
    //     }
	// }

	// for(int i = 0; i < NUM_OF_UTENTI; i++){
	// 	pthread_join(thread_id[i], NULL);
	// }
	// pthread_mutex_destroy(&mutex);
	// printStanze(&stanze);


}