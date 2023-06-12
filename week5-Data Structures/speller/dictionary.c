#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    bool check = false;
    // Hash word to obtain a hash value
    unsigned int hash_value = hash(word);

    // Access linked list at that index in hash table
    node *cursor = table[hash_value];

    // Traverse linked list, looking for word (case-insensitive)
    while (cursor != NULL)
    {
        // Convert both words to lowercase before comparing them
        char lowercase_word[LENGTH + 1];
        char lowercase_cursor_word[LENGTH + 1];
        strcpy(lowercase_word, word);
        strcpy(lowercase_cursor_word, cursor->word);
        for (int i = 0; lowercase_word[i]; i++)
        {
            lowercase_word[i] = tolower(lowercase_word[i]);
        }
        for (int i = 0; lowercase_cursor_word[i]; i++)
        {
            lowercase_cursor_word[i] = tolower(lowercase_cursor_word[i]);
        }
        // Compare the lowercase words
        if (strcmp(lowercase_cursor_word, lowercase_word) == 0)
        {
            check = true;
            break;
        }
        cursor = cursor->next;
    }
    return check;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // A simple hash function that returns the index of the first letter of the word
    // (assuming that the word contains only alphabetical characters)
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy word into node
        strcpy(new_node->word, word);

        // Hash word to obtain a hash value
        unsigned int hash_value = hash(word);

        // Insert node into hash table at that index
        new_node->next = table[hash_value];
        table[hash_value] = new_node;
    }

    // Close file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Traverse hash table and count nodes
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse hash table and free nodes
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}