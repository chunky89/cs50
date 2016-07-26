/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    /**
     * 0. create a dictionary
     * 1. declare a file pointer and open the dictionary
     * 2. scan every word in the dictionary, load it to the data structure
     * 3. close the file
     * 4. return true
    **/
    
    dict d = createDictionary(); 
    FILE *fp = fopen(dictionary, "r");
    assert(fp != NULL);
    // temporary storage
    char x[LENGTH+1];
    /* assumes no word exceeds length of 45 */
    while (fscanf(fp, " %1023s", x) == 1) {
        // load it to the data structure
    }

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

int hash(int letter)
{
    return letter - 'a';    
}

link create_node(const char *word)
{
    // this function accepts a word and create a node with this word
    link newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    
    strcpy(newNode->word, word);
    newNode->next = NULL;
    
    return newNode;
}

link insertNode(link head, link node)
{
    // node->next = head;
    // head = node;
    
    // return head;
    
    link next_node = head;
    link prev_node = NULL;
    
    while(next_node && strcmp(node->word, next_node->word) >0) 
    {
        prev_node = next_node;
        next_node = next_node->next; // find correct position
    }
    
    if(prev_node == NULL)
    {
        head = node;
    }
    else 
    {
        prev_node->next = node; // link inserting node into list 
    }
    node->next = next_node;
    
    return head;
}

dict createDictionary(void)
{
    // allocate memory for an array of linked list
    dict newDict = malloc(NUMBER_OF_ALPHABETS * sizeof(struct dictNode));
    assert(newDict != NULL);
    
    // initialize the node pointer and size
    for(int i = 0; i<NUMBER_OF_ALPHABETS; i++)
    {
        newDict[i].letter = NULL;
        newDict[i].n = 0;
    }
    
    return newDict;
}
