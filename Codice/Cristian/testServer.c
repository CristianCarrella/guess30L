#include<sys/types.h>

//Per le socket
#include<sys/socket.h>
#include <netinet/in.h>  
#include <netdb.h> 

#define MAX 80

//Librerie Progetto
//#include "../__Final__/database.h"
#include "../__Final__/strutture.h"

//librerie di test
#include "./Header/testDb.h"

int main(){
    int fd1, fd2, childpid;
    struct sockaddr_in myaddress;
    char buf[MAX];
    const int PORT = 3000;
    PGconn *conn = PQconnectdb("host=host.docker.internal port=49156 user=postgres password=postgrespw");
	
    if (PQstatus(conn) == CONNECTION_BAD) {
        
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
            
        PQfinish(conn);
    }   
    
/*  TEST LOGIN

    utente *utente1 = new_utente("angryzebra765", "racing", "em@email.it", 15);
    utente *utente2 = new_utente("beautifulladybug845", "trick", "kai.menard@example.com", 3);
	
    if(loginQuery(conn, utente1->username , utente1->passw)){
    	printf("Loggato\n");
	}else{
		printf("NON Loggato\n");
	}
*/

    fd1 = socket(AF_INET, SOCK_STREAM, 0);
    if(fd1 < 0){
    	printf("Errore nello stabilire la connessione\n");
    	exit(0);
	}else{
		printf("Socket creata con successo :)\n");
	}
	
    myaddress.sin_family = AF_INET;
    myaddress.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddress.sin_port = htons(PORT);
    
    if(bind(fd1, (struct sockaddr *) &myaddress, sizeof(myaddress)) != 0){
    	printf("Bind della socket fallito\n");
    	exit(0);
	}else{
		printf("Bind avvenuto con successo :)\n");
	}
	
    if((listen(fd1, 5)) != 0){
    	printf("Listening fallito\n");
		exit(0);	
	}else{
		printf("Il server è in listening :)\n");
	}
	
	while (1) {
		
	    fd2 = accept(fd1, NULL, NULL);
	    if(fd2 < 0){
	    	printf("In attesa di nuovi Client\n");
	    	exit(0);
		}else{
			printf("Nuovo Client accettato :)\n");
		}
		//da fare con i thread e da vedere meccanismi di sincronizzazione qualora ci fossero problemi
		if ((childpid = fork()) == 0) {
			close(fd1);
			read(fd2, buf, sizeof(buf));
			printf("%s\n", buf);
			
		}
		
	}
	close(fd2);
    
    
}
