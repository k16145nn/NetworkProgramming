#include <stdio.h>

struct money2
{
    int deposit;
    unsigned short numDeps;
    int withdraw;
    unsigned short numWithdraw;
};
struct money3
{
    int deposit;
    int withdraw;
    unsigned short numDeps;
    unsigned short numWithdraw;
};
struct money4
{
    int deposit;
    unsigned short numDeps;
    unsigned short numWithdraw;
};
struct money5
{
    unsigned short numDeps;
    unsigned short numWithdraw;
    int deposit;
    int withdraw;
};
struct money6
{
    unsigned short numDeps;
    int deposit;
    unsigned short numWithdraw;
};
struct money7
{
    unsigned short numDeps;
    unsigned short numWithdraw;
    unsigned short kozima;
};

int main(int argc, char *argv[])
{
    printf("%lu バイトル\n", sizeof(int));
    printf("%lu バイトル\n", sizeof(unsigned short));
    printf("%lu バイトル\n", sizeof(struct money2));
    printf("%lu バイトル\n", sizeof(struct money3));
    printf("%lu バイトル\n", sizeof(struct money4));
    printf("%lu バイトル\n", sizeof(struct money5));
    printf("%lu バイトル\n", sizeof(struct money6));
    printf("%lu バイトル\n", sizeof(struct money7));
    return 0;
}
