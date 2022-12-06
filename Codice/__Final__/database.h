#include<stdio.h>
#include<stdlib.h>
//sudo apt-get install libpq-dev
#include"/usr/include/postgresql/libpq-fe.h"

//Inserisce una nuova stanza nel Database. Ritorna l'ID generato della stanza, -1 per errori)
int db_insertStanza(PGconn *dbconn, char adminUsername[32], char roomName[16], int maxGiocatori, int privato, char keyword[16])
{
    char queryString[512] = "INSERT INTO stanza VALUES(default, '";
    char str[16];
    //Nome della stanza
    strcat(queryString, roomName);
    strcat(queryString, "', ");
    //Max Giocatori
    sprintf(str, "%d", maxGiocatori);
    strcat(queryString, str);
    strcat(queryString, ", ");
    //Private
    if(privato)
        strcpy(str, "true");
    else
        strcpy(str, "false");
    strcat(queryString, str);
    strcat(queryString, ", '");
    //Keyword
    strcat(queryString, keyword);
    strcat(queryString, "', '");
    //Admin
    strcat(queryString, adminUsername);
    strcat(queryString, "') RETURNING idStanza;");
    //
    printf("QUERY: %s\n", queryString);
    PGresult *res = PQexec(dbconn, queryString);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "failed: %s\n", PQerrorMessage(dbconn));
        PQclear(res);
        return -1;
    }
    char *resultValue = PQgetvalue(res, 0, 0);
    PQclear(res);
    int idvalue = atoi(resultValue);
    return idvalue;
}

//Inserisce la partecipazione di un utente ad una stanza nel db. Ritorna 1 in caso di successo, 0 in caso di fallimento
int db_insertUtenteToStanza(PGconn *dbconn, int idStanza, char username[32])
{
    char queryString[512] = "UPDATE utente SET idStanza = ";
    char *str;
    sprintf(str, "%d", idStanza);
    strcat(queryString, str);
    strcat(queryString, " WHERE username = '");
    strcat(queryString, username);
    strcat(queryString, "';");
    printf("QUERY: %s\n", queryString);
    PGresult *res = PQexec(dbconn, queryString);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "failed: %s\n", PQerrorMessage(dbconn));
        PQclear(res);
        return -1;
    }
    return 0;
}

//Controlla che l'username e la password dati come parametri esistano nel database, ritorna true se vero altrimenti false
bool loginQuery(PGconn *conn, char username[32], char password[16]){
	
	char queryString[512] = "SELECT * FROM utente WHERE username = '";
	strcat(queryString, username);
	strcat(queryString, "' AND passw = '");
	strcat(queryString, password);
	strcat(queryString, "'");
	
	printf("\nQUERY: %s ", queryString);
	
	PGresult * res = PQexec(conn, queryString);
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
		printf("NON nel db\n");
	}
	else{
		printf("Presente nel db\n"); 
		int rows = PQntuples(res);   
		if(rows > 0){
			return true;
		}
		return false;
	}
	PQclear(res);
    return false;   
}
