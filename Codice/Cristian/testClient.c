#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>  
#include <netdb.h> 
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#define UNIX_PATH_MAX 108
#define MAX 80


int main()
{
	
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    char buf[MAX] = "ciao";
    const int PORT = 3000;
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Errore nello stabilire la connessione\n");
        exit(0);
    }
    else{
        printf("Socket creata con successo :)\n");
 	}
 	
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
 
    if (connect(sockfd, (struct sockaddr_in *)&servaddr, sizeof(servaddr)) != 0) {
        printf("Errore nello stabilire la connessione\n");
        exit(0);
    }
    else{
        printf("Connesso al Server\n");
 	}
 	
    write(sockfd, buf, sizeof(buf));
    close(sockfd);
    
}

