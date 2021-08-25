// Implements a dictionary's functionality

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Establish a counter for the number of words and a bool to track unloading
int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Establish a pointer that helps sort through the dictionary
    int location = hash(word);
    node *cursor = table[location];

    // Search for the word in the dictionary
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Run the hash function http://www.cse.yorku.ca/~oz/hash.html
    int hash = 5381;
    int c = 0;

    while (c == *word)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
   return hash;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }
    char word [LENGTH];
    // Scan the file
    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Move the words from the dictionary into the hash table
        strcpy(n->word, word);
        int location = hash(word);
        n->next = table[location];
        table[location] = n;

        // Update the word counter
        count++;
    }
    // Close files
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the word count
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // Iteratively free all of the memory we used
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;

        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
