#include "database.h"
#include "word.h"
#include "main.h"
// sudo apt install libjson-c-dev
#include <json-c/json.h>

void checkConnectionToDb(PGconn *conn){
	if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
            PQerrorMessage(conn));
        PQfinish(conn);
    }else{
		printf("Successful connected to database [V]\n");
	}
}


typedef struct thread_par {
    int new_socket;
    PGconn* conn;
} thread_par;


void *handle2_client(void *par_) {
    thread_par par = *(thread_par*)par_;
    int socket = par.new_socket;
    PGconn * conn = par.conn;
    char buffer[2048] = {0};
    
    printf("New client connected.\n");
    
    while (1) {
		
        if ((read(socket, buffer, 2048)) == 0) {
            printf("Client disconnected.\n");
            break;
        }
        
        printf("Received message from client: %s\n", buffer);

        struct json_object *js = json_tokener_parse(buffer);
        const char *operation = json_object_get_string(json_object_object_get(js, "operation"));

		if(strcmp(operation, "login") == 0){
			char* email = (char*) json_object_get_string(json_object_object_get(js, "email"));
			char* password = (char*) json_object_get_string(json_object_object_get(js, "password"));

			utente* utente = login(conn, email, password, socket);
            if(utente != NULL){
                printf("Login avvenuto con successo!\n");
            }else{
                printf("Login fallito\n");
            }
		}
		else if(strcmp(operation, "signup") == 0){
			char* email = (char*) json_object_get_string(json_object_object_get(js, "email"));
			char* password = (char*) json_object_get_string(json_object_object_get(js, "password"));
			char* username = (char*) json_object_get_string(json_object_object_get(js, "username"));
            if(signUp(conn, username, password, email)){
                printf("Signup avvenuto con successo!\n");
            }else{
                printf("Signup fallito\n");
            }
		}

        if (send(socket, "Message received.", 17, 0) == -1) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }
        printf("\n\n");

        memset(buffer, 0, sizeof(buffer));
    }
    
    close(socket);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;
    thread_par par;
    par.conn = PQconnectdb("postgresql://user:admin@172.20.0.3:5432/lso"); //sudo docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' container_name
	checkConnectionToDb(par.conn);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Server started listening on port %d...\n", PORT);
    
    while (1) {
        if ((par.new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }
        
        if (pthread_create(&thread_id, NULL, handle2_client, (void *)&par) < 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}
