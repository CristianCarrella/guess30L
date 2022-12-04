//Per la connessione al database
#include <libpq-fe.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void endConnection(PGconn *conn);
bool loginQuery(PGconn *conn, char username[32], char password[16]);
