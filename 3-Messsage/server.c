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
void read_until_delim(int, char *, char, int);
int get_current_balance();
void set_current_balance(int);
void read_certain_bytes(int, void *, int);

struct money
{
    int deposit;
    int withdraw;
};

int main(int argc, char *argv[])
{
    struct sockaddr_in clientAddress;
    unsigned int szClientAddr;
    int cliSock;

    int servSock = prepare_server_socket(10001);

    listen(servSock, 5); //順番待ちマテル数５//

    while (1)
    {
        szClientAddr = sizeof(clientAddress);
        cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);
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
    int servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (servSock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in servAddress;
    servAddress.sin_family = AF_INET;
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddress.sin_port = htons(port);

    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
    int len_r = 0;
    int index_letter = 0;

    while (index_letter < max_length - 1)
    {
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
        {

            printf("接続が切れました\n");
            return;
        }
        if (buf[index_letter] == delimiter)
            break;
        else
            index_letter++;
    }
    buf[index_letter] = '\0';
}

int get_current_balance()
{
    return 1000000;
}

void set_current_balance(int new_balance)
{
    return;
}

void commun(int sock)
{
    int balance = get_current_balance();

    struct money msgMoney;

    read_certain_bytes(sock, &msgMoney, (int)sizeof(msgMoney));
    balance += msgMoney.deposit;
    balance -= msgMoney.withdraw;

    set_current_balance(balance);

    if (send(sock, &balance, sizeof(balance), 0) != sizeof(balance))
        DieWithError("send() sent amessage of unexpected bytes");
}

void read_certain_bytes(int sock, void *buf, int length)
{
    int len_r = 0;
    int len_sum = 0;

    while (len_sum < length)
    {
        if ((len_r = recv(sock, buf + len_sum, length - len_sum, 0)) <= 0)
            DieWithError("recv() failed");
        len_sum += len_r;
    }
}