/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define NUMBER_OF_ALPHABETS 26

/**
 * Data structure of the linked list
**/
typedef struct node* link;
struct node
{
    char word[LENGTH+1];
    link next;
};

/**
 * Data structure of the dictionary - an array of linked list
 
 * For each dictionary node, it contains the number of words belongs
 * to a particular buckets and a linked list
**/
typedef struct dictNode* dict;
struct dictNode
{
    int n;  // keep track of number of words
    link letter;  // an array of linked list
};


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Generate corresponding index for a letter, return 0 if the letter is 'a'
 * return 1 if the letter is 'b' and so on.
**/
int hash(int letter);

/**
 * Create a new node containing a word. Return a pointer to this node.
**/
link createNode(const char *word);

/**
 * Insert the node to the head of the linked list. Return the new head of the linked list.
**/
link insertNode(link head, link node);

/**
 * Create a dictionary data structure and initialize it. Return a pointer to this dictionary. 
**/
dict createDictionary(void);

#endif // DICTIONARY_H
