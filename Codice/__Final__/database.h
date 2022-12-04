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
