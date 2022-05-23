#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>

int main(int argc, string argv[])
{
    // extract salt for crypt function
    char *salt = malloc (3);
    salt [0] = argv[1][0];
    salt [1] = argv[1][1];
    salt [2] = '\0';
    printf("serching...");

    // iterations counter
    int counter = 0;
    
    //our hash to be compared with the hash from argv
    char *hashx = malloc (14);
    hashx [13] = '\0';

    //our possible password
    char *x = malloc (6);
    x [5] = '\0';

    for (int i4 = 65; i4<123; i4++)
    {
        for (int i3 = 65; i3<123; i3++)
        {
            for (int i2 = 65; i2<123; i2++)
            {
                for (int i1 = 65; i1<123; i1++)
                {
                    for (int i0 = 65; i0<123; i0++)
                    {
                        if (i0 == 91)
                            {
                                i0 = 97;
                            }
                        x[0] = i0;
                        hashx = crypt (x, salt);
                        counter ++;
                        if (strcmp (hashx, argv[1]) == 0)
                            {
                                printf ("\nNumber of iterations: %i\n", counter);
                                printf ("Password is: %s\n", x);
                                return 0;
                            }
                    }
                    if (i1 == 91)
                        {
                            i1 = 97;
                        }
                    x[1] = i1;
                }
                if (i2 == 91)
                    {
                        i2 = 97;
                    }
                x[2] = i2;
            }
            if (i3 == 91)
                {
                    i3 = 97;
                }
            x[3] = i3;
        }
        if (i4 == 91)
            {
                i4 = 97;
            }
        x[4] = i4;
    }
    printf("\nMatches not found.\n");
    return 0;
}

