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
void my_scanf

    int
    main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("usage: ./client ip_address port")

            void
            DieWithError(char *errorMessage)
        {
            perror(errorMessage);
            exit(1);
        }

    int prepare_client_socket(char *)
}
}