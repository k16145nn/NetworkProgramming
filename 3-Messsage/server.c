#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_server_socket(int);
void commun(int);

int main(int argc, char[])
{
    struct sockaddr_in clientAddess;
    unsigned int szClientAddr;
    int cliSock;

    int servSock = prepare_server_socket(10001);

    listen(servSock, 5); //順番待ちマテル数５//

    while (1)
    {
        szClientAddr = sizeof(clientAddess);
        cliSock = accept(servSock, (struct sockaddr *)&clientAddess, &szClientaddr);

        commun(cliSock);

        close(cliSock);
    }
    close(servSock);
    return 0;
}

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int prepare_server_socket(int port)
{
    int servSock = socket(PF_INET, SOCK_STREA, 0);
    if (servSock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in servAddress;
}