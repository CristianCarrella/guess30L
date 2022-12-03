//per compilare: gcc -I /usr/include/postgresql -L/usr/lib -o prova main.c -lpq
#include"/usr/include/postgresql/libpq-fe.h"
#include<stdio.h>
#include<stdlib.h>
#include"Federico/postgresql"


int main()
{
    char *message;
    //const char* conninfo = "postgresql://postgres:postgres@localhost:5432/postgres";
    const char* conninfo = "host=localhost port=5432 dbname=postgres user=fedegar password=fedegar";
    const char* command = "CREATE TABLE prova3 (attr2 VARCHAR(10));";
    
    PGconn *dbconn = PQconnectdb(conninfo);
    if (PQstatus(dbconn) != CONNECTION_OK)
    {
        fprintf(stderr, "%s", PQerrorMessage(dbconn));
        exit(1);
    }

    message = PQdb(dbconn);
    printf("Sei connesso al DB %s\n", message); 
    
    PGresult *res = PQexec(dbconn, command);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "SET failed: %s\n", PQerrorMessage(dbconn));
        PQclear(res);
        exit(1);
    }
    
}