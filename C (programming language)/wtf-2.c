#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

int main(void)
{
    char *x = malloc (14);
    x = "qwerty";

    char *y = malloc (14);
    y = "asdfgfhgj";

    char *z = malloc (14);
    z = "1234345";

    printf("heshx = %s\n", x);
    printf("heshy = %s\n", y);
    printf("heshz = %s\n", z);

    return 0;
}