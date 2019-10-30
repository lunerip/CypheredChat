#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 100
#define PORT 8080
#define SA struct sockaddr


void func(int sockfd)
{
    char buff[MAX];
    int n;
    do{
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }while(true);
}


int main(){
    int socketfd;
    int connfd;
    int len;
    struct sockaddr_in serverAdd;
    struct sockaddr_in cli;

    struct serverAdd;

    // Creation of a Socket with TCP
    socketfd = socket(AF_INET, SOCK_STREAM,0);

    // Gives feedback in case of a failure on the socket creation
    if(socketfd<0){
        printf("Failed socket connection. Try later.");
        exit(0);
    }

    bzero(&serverAdd, sizeof(serverAdd));


    // Assigns an IP address to the server
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);

    // Assigns the port to the server
    serverAdd.sin_port = htons(PORT);

    // Binds socket
    if(bind(socketfd, (SA*)&serverAdd, sizeof(serverAdd))<0){
        printf("Failed socket connection. Try later.");
        exit(0);
    }

    // Server's listening with 32 connections
    if(listen(socketfd, 32))<0){
        printf("Failed socket connection. Try later.");
        exit(0);
    }

    len = sizeof(cli);

    // Establishes connection with client
    connectionfd = accept(socketfd, (SA*)&cli, &len);

    if (connfd < 0) {
        printf("Failed connection with client. Try later.");
        exit(0);
    }

    chat(connectionfd);

    // Closes the socket
    close(socketfd);
    return 0;
}
