#include<sys/types.h>

//Per le socket
#include<sys/socket.h>
#include <netinet/in.h>  
#include <netdb.h> 

#define MAX 80

//Librerie Progetto
#include "../__Final__/database.h"
#include "../__Final__/strutture.h"


int main(){
    int fd1, fd2, childpid;
    struct sockaddr_in myaddress;
    char buf[MAX];
    const int PORT = 3000;
    
    
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
