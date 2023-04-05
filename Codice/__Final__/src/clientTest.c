#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <json-c/json.h>

#define PORT 5000

char* prepareLogin(){
    char email[30];
    char password[30];
    printf("Inserisci email: ");
    scanf("%s", email);
    printf("Inserisci password: ");
    scanf("%s", password);

    // Creare un oggetto JSON
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "operation", json_object_new_string("login"));
    json_object_object_add(json, "email", json_object_new_string(email));
    json_object_object_add(json, "password", json_object_new_string(password));
    
    free(json);
    // Convertire l'oggetto JSON in una stringa
    const char *jsonStr = json_object_to_json_string(json);
    return (char*)jsonStr;
}

char* prepareSignup(){
    char email[30];
    char password[30];
    char username[30];
    printf("Inserisci username: ");
    scanf("%s", username);
    printf("Inserisci email: ");
    scanf("%s", email);
    printf("Inserisci password: ");
    scanf("%s", password);

    // Creare un oggetto JSON
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "operation", json_object_new_string("signup"));
    json_object_object_add(json, "email", json_object_new_string(email));
    json_object_object_add(json, "password", json_object_new_string(password));
    json_object_object_add(json, "username", json_object_new_string(username));

    // Convertire l'oggetto JSON in una stringa
    const char *jsonStr = json_object_to_json_string(json);
    return (char*)jsonStr;
}

char* prepareGetAvatar(){
    char email[30];
    printf("Inserisci l'email dell'utente del quale si vuole l'avatar: ");
    scanf("%s", email);
    printf("%s", email);

    // Creare un oggetto JSON
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "operation", json_object_new_string("getAvatar"));
    json_object_object_add(json, "email", json_object_new_string(email));
    
    // Convertire l'oggetto JSON in una stringa
    const char *jsonStr = json_object_to_json_string(json);
    return (char*)jsonStr;
}

char* prepareSetAvatar(){
    int avatarType = 0;
    char email[30];
    printf("Inserisci l'email dell'utente del quale si vuole settare l'avatar: ");
    scanf("%s", email);
    printf("Inserisci il tipo di avatar (0, 15): ");
    scanf("%d", &avatarType);

    // Creare un oggetto JSON
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "operation", json_object_new_string("setAvatar"));
    json_object_object_add(json, "email", json_object_new_string(email));
    json_object_object_add(json, "avatarType", json_object_new_int(avatarType));
    
    // Convertire l'oggetto JSON in una stringa
    const char *jsonStr = json_object_to_json_string(json);
    return (char*)jsonStr;

}

char* prepareGetUserInfo(){
    char email[30];
    printf("Inserisci l'email dell'utente del quale si vogliono le informazioni: ");
    scanf("%s", email);

    // Creare un oggetto JSON
    struct json_object *json = json_object_new_object();
    json_object_object_add(json, "operation", json_object_new_string("getUserInfo"));
    json_object_object_add(json, "email", json_object_new_string(email));
    
    // Convertire l'oggetto JSON in una stringa
    const char *jsonStr = json_object_to_json_string(json);
    return (char*)jsonStr;
}

char* prepareOperation(int op){
    
    switch(op){
        case 1:
            return prepareLogin();
        break;
        case 2:
            return prepareSignup();
        break;
        case 3:
            return prepareGetAvatar();
        break;
        case 4:
            return prepareSetAvatar();
        break;
        case 5:
            return prepareGetUserInfo();
        break;
    }
}

int main(int argc, char *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *json = "";
    int op = 0;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    while(1) {
        printf("1. Login\n2. Signup\n3. GetAvatar\n4. SetAvatar\n5. GetUserInfo\n");
        scanf("%d", &op);
        json = prepareOperation(op);

        if (send(sock, json, strlen(json), 0) == -1) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }
        printf("Message sent to server: %s\n", json);
        
        if ((valread = read(sock, buffer, 1024)) == 0) {
            printf("Server disconnected.\n");
        }
        else {
            printf("Reply from server: %s\n", buffer);
        }
    }

    
    close(sock);
    
    return 0;
}