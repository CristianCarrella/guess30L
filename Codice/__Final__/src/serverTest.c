#include "../header/database.h"
#include "../header/word.h"
#include "../header/main.h"
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
        struct json_object *json = json_object_new_object();

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
        else if(strcmp(operation, "getAvatar") == 0){
            char* email = (char*) json_object_get_string(json_object_object_get(js, "email"));
            char* base64image_encoded = getAvatarByEmail(conn, email);

            json_object_object_add(json, "email", json_object_new_string(email));
            json_object_object_add(json, "avatarBase64", json_object_new_string(base64image_encoded)); //al client arriverà con dei backslash in più
        }
        else if(strcmp(operation, "setAvatar") == 0){
            char* email = (char*) json_object_get_string(json_object_object_get(js, "email"));
            int avatarType = (int) json_object_get_int(json_object_object_get(js, "avatarType"));
            bool result = setAvatarOfUser(conn, email, avatarType);

            json_object_object_add(json, "email", json_object_new_string(email));
            json_object_object_add(json, "isSuccess", json_object_new_boolean(result));
        }
        else if(strcmp(operation, "getUserInfo") == 0){
            char* email = (char*) json_object_get_string(json_object_object_get(js, "email"));
            utente* u = getUserByEmail(conn, email, -1);

            json_object_object_add(json, "email", json_object_new_string(email));
            json_object_object_add(json, "idStanza", json_object_new_int(u->idStanza));
            json_object_object_add(json, "imgId", json_object_new_int(u->imgId));
            json_object_object_add(json, "partiteVinte", json_object_new_int(u->partiteVinte));
            json_object_object_add(json, "username", json_object_new_string(u->username));
            free(u);

        }
        else if(strcmp(operation, "joinRoom") == 0){
            
        }
        else if(strcmp(operation, "searchRoom") == 0){
            
        }
        else if(strcmp(operation, "createRoom") == 0){
            
        }
        else if(strcmp(operation, "startGame") == 0){
            
        }

        const char *jsonStr = json_object_to_json_string(json);
        printf("JSON response: %s", jsonStr);
        //dovrà inviare al client jsonStr
        //free(json);

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
    par.conn = PQconnectdb("postgresql://user:admin@localhost:54320/postgres"); //sudo docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' container_name
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
