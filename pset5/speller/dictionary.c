// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Keep track of word count in dictionary
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Obtain hash value
    int hashVal = hash(word);

    // Access linked list at that index in hash table
    node *cursor = table[hashVal];

    // Traverse linked list, looking for the word (case insensitive)
    for (; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);

        // Obtain hash value
        int hashVal = hash(word);

        // Insert node into hash table
        n->next = table[hashVal];
        table[hashVal] = n;

        count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (count > 0)
    {
        return count;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        // Traverse linked list, freeing up space
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            count--;
        }
    }

    if (count == 0)
    {
        return true;
    }

    return false;
}
