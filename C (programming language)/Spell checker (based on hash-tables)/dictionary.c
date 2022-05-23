// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
        
    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        //node to be added to a hashtable
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return 1;
        }
        
        //defines the number of hastable for the word
        int hnum = hash (word);
        
        //puts a word into a node
        for (int i = 0; i <= strlen(word); i++)
        {
            n->word[i] = word[i];
        }
        n->next = NULL;
        
        //saves word into a node
        if (hashtable [hnum] == NULL)
        {
            hashtable [hnum] = n;
        }
        else
        {
            for (node *ptr = hashtable [hnum]; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = hashtable [i]; ptr != NULL; ptr = ptr->next)
            {
                counter++;
            }
    }
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash (word);
    if (hashtable [h] == NULL)
    {
        return false;
    }
    else
    {
        for (node *ptr = hashtable [h]; ptr != NULL; ptr = ptr->next)
        {
            int strl = strlen(word);
            if (strl == strlen(ptr->word))
            {
                int counter = 0;
                for (int i = 0; i < strl; i++) 
                {
                    if (tolower(ptr->word[i]) == tolower(word [i])) 
                    {
                        counter ++;
                        if (counter == strl)
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable [i];
        while (cursor != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free (temp);
            }
    }
    return true;
}