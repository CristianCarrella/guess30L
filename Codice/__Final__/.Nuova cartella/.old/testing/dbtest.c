#include"dbtest.h"
void signupTest(PGconn* conn){
	printf("TEST SIGNUP USER START\n");
	char email[64] = "provae";
	char password[16] = "provap";
	char username[32] = "prova";
	if(signUp(conn, email, password, email)){
		printf("\033[1;32m[V] Test passed - Account not registered [Already registered || Error]\033[0m\n");
	}else{
		printf("\033[1;32m[V] Test passed - Account registered\033[0m\n");
	}
	printf("TEST SIGNUP USER END\n\n");
}

void loginTestUserExist(PGconn* conn, int socket){
	printf("TEST LOGIN USER EXIST START\n");
	char email[32] = "provae";
	char password[16] = "provap";
	utente *utente = login(conn, email, password, socket);
	if(utente != NULL){
		printf("\033[1;32m[V] Test passed - Login Success\033[0m\n");
	}else{
		printf("\033[1;31m[X] Test failed - Login Failed\033[0m\n");
	}
	printf("TEST LOGIN USER EXIST END\n\n");
}

void loginTestUserNotExist(PGconn* conn, int socket){
	printf("TEST LOGIN USER NOT EXIST START\n");
	char email[32] = "prova";
	char password[16] = "xxx";
	utente *utente = login(conn, email, password, socket);
	if(utente == NULL){
		printf("\033[1;32m[V] Test passed - Login Fail\033[0m\n");
	}
	printf("TEST LOGIN USER NOT EXIST END\n\n");
}

void updatePartiteVinteTest(PGconn* conn, int socket){
    printf("TEST UPDATE PARTITE VINTE START\n");
    char email[64] = "provae";
    utente * u = getUserByEmail(conn, email, socket);
    printf("Email : %s\nPartite Vinte: %d\n", u->email, u->partiteVinte);
	printf("Aggiunta di 15 vittorie...\n");
	updateUserPartiteVinte(conn, email);
	u = getUserByEmail(conn, email, socket);
	printf("Email : %s\nPartite Vinte: %d\n", u->email, u->partiteVinte);
    printf("\033[1;32m[V] Test passed - Update success\033[0m\n");
    printf("TEST UPDATE PARTITE VINTE END\n");
}

void testAvatar(PGconn* conn){
	char email[64] = "provae";
	setAvatarOfUser(conn, email, 1);
	getAvatarByEmail(conn, email);
}