// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 90;

int counter = 0;
char buffer[LENGTH + 1];

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // recieve value to check same location in hash table
    int n = hash(word);
    node *cursor = table[n];
    node *tmp = NULL;


    // Check the nodes in linked list for word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i = strlen(word);
    int a = 0;
    int n = toupper(word[0]) - 'A';

    if (n < 13)
    {
        a = i;
    }
    else
    {
        a = N - i;
    }
    return a;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // While loop until no words left in file
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // allocate memory for a node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return 1;
        }

        // Keep track of number of words
        counter++;
        // copy the word from the buffer into the node
        strcpy(n->word, buffer);

        // hash the word into a value for the hash table
        int i = hash(n->word);
        if (table[i] == NULL)
        {
            n->next = NULL;
        }

        // Assign the words into linked lists in the hash table
        n->next = table[i];
        table[i] = n;
    }

    printf("%i\n", counter);

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp = NULL;
    node *cursor = NULL;
    // TODO
    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        cursor = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
