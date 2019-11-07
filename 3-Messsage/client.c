#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_client_socket(char *, int);
void my_scanf(char *, int);
void commun(int);
void read_until_delim(int, char *, char, int);
void read_certain_bytes(int, void *, int);

struct money
{
    int deposit;
    int withdraw;
};

int main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port");

    int sock = prepare_client_socket(argv[1], atoi(argv[2]));

    commun(sock);

    close(sock);

    return 0;
}
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int prepare_client_socket(char *ipassr, int port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = htonl(INADDR_ANY);
    target.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *)&target, sizeof(target)) < 0)
        DieWithError("connect() failed");

    return sock;
}

void my_scanf(char *buf, int num_letter)
{

    char format[20];
    sprintf(format, "%s%d%s", "%", num_letter, "s%*[^\n]");
    scanf(format, buf);
    getchar();
}
void commun(int sock)
{
    char cmd[2] = "";
    struct money msgMoney;
    char money[BUF_SIZE];
    int result;

    printf("0:引き出し　1:預け入れ 2:残高参照 \n");
    printf("何をしますか? > ");

    my_scanf(cmd, 1);

    switch (cmd[0])
    {
    case '0':
        printf("引き出す金額を入力してください > ");
        my_scanf(money, MONEY_DIGIT_SIZE);
        msgMoney.deposit = 0;
        msgMoney.withdraw = atoi(money);
        break;
    case '1':
        printf("預け入れる金額を選んでください > ");
        my_scanf(money, MONEY_DIGIT_SIZE);
        msgMoney.deposit = atoi(money);
        msgMoney.withdraw = 0;
        break;
    case '2':
        msgMoney.deposit = 0;
        msgMoney.withdraw = 0;
        break;
    default:
        printf("番号が確認できませんでした.\n");
        return;
    }

    printf("%lu バイトするならタウンワーク\n", sizeof(msgMoney));
    if (send(sock, &msgMoney, sizeof(msgMoney), 0) != sizeof(msgMoney))
        DieWithError("send()sent a message of unexpected dytes");

    read_certain_bytes(sock, &result, (int)sizeof(int));
    printf("残高は%d円になりました", result);
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