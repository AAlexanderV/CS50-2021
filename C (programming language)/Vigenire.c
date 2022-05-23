#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

char encrypt (char, int); //encrypts a word per Char, using "key"

int main(int argc, string argv[])
{
    //if key is not indicated or too many arguments, finishes programm
    if (argc != 2) 
        {
         printf("Error.\nUsage: ./vigenere keyword\n");
         return 1;
        }

    int ssa = strlen (argv[1]);
    int key[ssa];

   //checks whether key consists from letters only
    for (int i=0; i<ssa; i++) 
    {
        if ((argv[1][i]<65)||((argv[1][i]>90)&&(argv[1][i]<97))||(argv[1][i]>122))
            {
             printf("Usage: ./vigenere keyword\n");
             return 1;
            }
    }    
    
    //converts small key-letters into big ones
    for (int i=0; i<ssa; i++) 
    {
        if ((argv[1][i]>96))
            {
             argv[1][i] = argv[1][i] - ('a'-'A');
             printf("%c", argv[1][i]);
            }
        else
        {
            printf ("%c", argv[1][i]);
        }   
        printf("\n");
    }   
    
    //converts key-letters into digits 0-32 or so
    for (int i=0; i<ssa; i++) 
    {
        key [i] = argv[1][i] - 'A';
        //FYI, Can be deleted
        printf("%i", key[i]); 
    }   

    //asks for words, which need to be encrypted 
    string word = get_string("Before:\n"); 
    printf("After: \n");

    //encryptes word char-by-char using "encrypt" function
    for (int i=0, n=strlen(word); i<n; i++) 
    {
        printf("%c", encrypt (word[i], key[i%ssa])); 
    }
printf("\n");
}


//FUNCTIONS
char encrypt (char x, int k)
{
    if ((x<65)||((x>90)&&(x<97))||(x>122)) //if the char is not a letter, returns it as it is
    {
        return x;
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            //changes char "k" times
            x++;                
            //starts counting from "A" in case we reached "Z"
            if ((x>90)&&(x<97)) 
            {
                x = 65;
            }
            //starts counting from "a" in case we reached "z"
            if (x>122) 
            {
                x = 97;
            }
        }
    return x;
    }
    
}
