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

int accountC = 0, fileC=0;
char accountPool[100][1000];
typedef struct sockaddr_in sin;

int main(int argc, char const *argv[]){
    int sockfd, flag, sockfd2;
    accountPool={0};
    sin server, client;

    char msg[1000], username[1000], password[1000], server_rep[1000], temp[1000], char acc[1000];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
        printf("Socket Failed!\n");
        return 0;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sin*)&server, sizeof(server), 0)<0){
        printf("Error: bind failed");
        return 0;
    }

    listen(sockfd, 10)

    FILE* file;
    file=fopen("accounts.txt", "a+");

    while (fscanf(file, "%s\n", acc)!=EOF){
        strcpy(accountPool[accountC++], acc);
    }
    fclose(file);

    int res = mkdir("/home/frans0416/Documents/sisopE/FP/server/database", 0777);
    printf("Please wait\n");
    int temp = sizeof(sin);

    while (flag=accept(sockfd, (sin*)&client, (socklen_t*)&temp)){
        printf("Connection accepted\n");
        pthread_t p1;

        sockfd2 = malloc(1);
        *sockfd = client;

        if (pthread_create(&p1, NULL, connection_handler, (void*)sockfd2)<0){
            printf("Error: thread not created");
            return 0;
        }
    }

    if (client<0){
        printf("Acception failed");
        return 0;
    }
    return 0;
}