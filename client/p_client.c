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

    uid_t uid=getuid(), euid=geteuid();
    char username[1000], password[1000];

    if (uid==0) {
        printf("Welcome Master!\n");
        strcpy(username, "admin");
        strcpy(password, "admin");

    } else if(argc!=5 || strcmp(argv[1], "-u")!=0 || strcmp(argv[1], "-p")!=0) {
        printf("Syntax Error!\n");
        return 0;
    }
    else{
        printf("Welcome!\n");
        trcpy(username, argv[2]);
        strcpy(password, argv[4]);
    }

    

    sin p_address;
    sin s_address = {0};

    //socket(domain, type, protocol)
    //domain -- AF_INET, AF_INET6
    //type -- SOCK_STREAM: TCP(reliable, connection oriented) -- SOCK_DGRAM: UDP(unreliable, connectionless)
    //protocol -- 0
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("Socket Failed!\n");
        return 0;
    }

    s_address.sin_family = AF_INET;
    s_address.sin_port = htons(PORT);

    int flag = inet_pton(AF_INET, "127.0.0.1", &s_address.sin_addr);
    if (flag<=0){
        printf("Error: Adress not found\n");
        return 0;
    }

    flag = connect(sockfd, (sin*)&s_address, sizeof(s_address));
    if (flag<0){
        printf("Error: Connection failed\n");
        return 0;
    }

    char temp[1000], server_rep[1000];
    temp={0};
    sprintf(temp, "%s-%s", username, password);

    //ssize_t send(int socket, const void *buffer, size_t length, int flags);
    //socket
    //Specifies the socket file descriptor.
    //buffer
    //Points to the buffer containing the message to send.
    //length
    //Specifies the length of the message in bytes.
    send(sockfd, temp, strlen(temp), 0);

    flag = recv(sockfd, server_rep, strlen(server_rep), 0);
    if (flag<0){
        printf("Error: failed recv\n");
    }
    if(strcmp(server_rep, "success")==0){
        printf("Login succesfull\n");
        send(sockfd, "s", 1, 0);
    }
    else{
        printf("Login failed\n");
    }
    printf("Hai");
    close(sockfd);
    return 0;
}