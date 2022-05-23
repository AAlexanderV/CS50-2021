#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

int main(int argc, string argv[])
{
    
    //our salt
    char *salt = malloc (3);
    salt [0] = argv[2][0];
    salt [1] = argv[2][1];
    salt [2] = '\0';
    //our future hash
    char *hashx = malloc (14);
    hashx [13] = '\0';
    
    //make hash
    hashx = crypt (argv[1], salt);
    
    printf ("Hash is: %s\n", hashx);
    return 0;
}

