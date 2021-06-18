#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h> 

typedef struct sockaddr_in sin;

int main(int argc, char const *argv[]){
    int sockfd;

    sin server;

    char msg[1000], username[1000], password[1000], server_rep[1000], temp[1000];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("Socket Failed!\n");
        return 0;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    int flag = inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (flag<=0){
        printf("Error: Adress not found\n");
        return 0;
    }

    flag = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (flag<0){
        printf("Error: Connection failed\n");
        return 0;
    }

    printf("Please wait...");

    recv(sockfd, server_reply, strlen(server_reply), 0);

    if (getuid!=0){
        strcpy(username, argv[2]);
        strcpy(password, argv[4]);
        sprintf(temp, "%s-%s", username, password)
        send(sockfd, temp, strlen(temp), 0);
        flag = recv(sockfd, server_rep, strlen(server_reply), 0);
    }
}