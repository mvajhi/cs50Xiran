// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 150;

// Hash table
node *table[N];

int wordcounter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int location = hash(word);
    node *cursor = table[location];
    char cword[LENGTH + 1];

    strcpy(cword, word);
    cword[strlen(word)] = '\0';
    while (cursor != NULL)
    {
        int x = strcasecmp(cursor->word, cword);
        if (x == 0)
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
    // TODO: Improve this hash function
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += (toupper(word[i]) - 'A');
    }
    return sum % N;
}
FILE *input;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }
    //for save word and copy in node
    char word[LENGTH + 1];
    while (fscanf(input, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        //if have not memory app close
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //copy word in node
        strcpy(new_node->word, word);

        int location = hash(word);
        node *head = table[location];
        new_node->next = table[location];
        table[location] = new_node;
        wordcounter++;
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordcounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //node *tmp = NULL;
    //node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
