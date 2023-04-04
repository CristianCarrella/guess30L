#ifndef DBTEST_H
#define DBTEST_H
#include "../database.h"
void updatePartiteVinteTest(PGconn* conn, int socket);
void loginTestUserNotExist(PGconn* conn, int socket);
void loginTestUserExist(PGconn* conn, int socket);
void signupTest(PGconn* conn);
#endif