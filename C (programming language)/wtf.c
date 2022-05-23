#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

int main(void)
{
    string x;
    string y;
    string z;

    x = crypt("qwerty","11");
    printf("heshx = %s\n", x);

    y = crypt("abcde","22");
    printf("heshy = %s\n", y);

    z = crypt("Abby","aa");
    printf("heshz = %s\n", z);

    printf("heshx = %s\n", x);
    printf("heshy = %s\n", y);
    printf("heshz = %s\n", z);

    return 0;
}