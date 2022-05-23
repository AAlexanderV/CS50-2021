// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie 
node *root;

//for a size function
unsigned int words_counter = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        int wstrl = strlen (word); // определить длинну слова
        node *ptr = root; //делаем временный поинтер, указывающий туда же, куда и РУТ
        for (int i = 0; i < wstrl; i++) // сделать это столько раз, сколько букв в слове
        {
            int index = tolower(word[i]) - 'a';//определяем индекс-ячейку для буквы, которая в обработке
            if (index < 0)
            {
                index = 26; //чтобы апостроф поместить в последнюю 26ю ячейку
            }
            if (ptr->children[index] == NULL)
            {
                node *new_node = malloc(sizeof(node)); //смотрим в ячейку с соотв-щим индексом и если она NULL создаем новый node для буквы
                if (new_node == NULL)// проверочка маллока
                {
                    return false;
                }
                for (int j = 0; j < N; j++) //инициализируем все буквы в NULL
                {
                    new_node->children[j] = NULL;
                }
                new_node->is_word = false; //если не последняя буква, то ложь
                ptr->children[index] = new_node;
            }
            ptr = ptr->children[index]; //входим в эту букву
            if (i == (wstrl - 1))//если это последняя буква в слове, то вставить истину
            {
                ptr->is_word = true;
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// void search_trie (struct node *trie)
// {
//     for (int i = 0; i < 27; i++)
//     {
//         if (trie->is_word == true)
//             {
//                 words_counter++;
//             }
//         if (trie->children[i] != NULL)
//         {
//             search_trie (trie->children[i]);
//         }
//     }
// }

void search_trie (struct node *trie)
{
     if (trie->is_word == true)
            {
                words_counter++;
            }
    for (int i = 0; i < 27; i++)
    {
       
        if (trie->children[i] != NULL)
        {
            search_trie (trie->children[i]);
        }
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    search_trie (root);
    return words_counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int wstrl = strlen (word); // определить длинну слова
    node *ptr = root; //делаем временный поинтер, указывающий туда же, куда и РУТ
    for (int i = 0; i < wstrl; i++)
    {
        int index = tolower(word[i]) - 'a';//определяем индекс-ячейку для буквы, которая в обработке
        if (index < 0)
            {
                index = 26; //чтобы апостроф поместить в последнюю 26ю ячейку
            }
        if (ptr->children[index] == NULL)
        {
            return false;
        }
        else
        {
            ptr = ptr->children[index];
        }
    }
    if (ptr->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void free_trie (struct node *trie)
{
    for (int i = 0; i < 26; i++)
    {
        if (trie->children[i] != NULL)
        {
                free_trie (trie->children[i]);
        }
    }

        free (trie);
}
    
// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (root != NULL)
    {
        free_trie (root);
        return true;
    }
    else
    {
        return false;
    }
}
