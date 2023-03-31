#ifndef DATABASE_H
#define DATABASE_H

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

//sudo apt-get install libpq-dev
#include"/usr/include/postgresql/libpq-fe.h"
#include"strutture.h" 
 
utente* login(PGconn *conn, char email[32], char password[16], int socket);
bool signUp(PGconn *conn, char username[32], char password[16], char email[64]);

#endif
