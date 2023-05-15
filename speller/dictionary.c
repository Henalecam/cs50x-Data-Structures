// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>



#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char lowerw[LENGTH + 1];
    int i = 0;
    while (word[i] != '\0')
    {
        lowerw[i] = tolower(word[i]);
        i++;
    }
    lowerw[i] = '\0';

    int hvalue = hash(lowerw);
    for (node *n = table[hvalue]; n != NULL; n = n -> next)
    {
        if (strcasecmp(n->word, lowerw) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash = (hash * 31) + word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer
    char word[LENGTH + 1];

    // Insert words
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word
        strcpy(n->word, word);

        // Hash word
        unsigned int h = hash(word);

        // Insert node
        n->next = table[h];
        table[h] = n;
    }

    // Close dictionary
    fclose(file);

    // success
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;

    // Traverse
    for (int i = 0; i < N; i++)
    {
        // Traverse linked list
        for (node *n = table[i]; n != NULL; n = n->next)
        {
            count++;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse
    for (int i = 0; i < N; i++)
    {
        // Traverse linked list
        while (table[i] != NULL)
        {
            node *n = table[i];
            table[i] = n->next;
            free(n); //freeing elements
        }
    }

    return true;
}