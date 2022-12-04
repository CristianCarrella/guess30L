//Per la connessione al database
#include <libpq-fe.h>
#include <stdio.h>

void do_exit(PGconn *, PGresult *);
void dbConnect();
