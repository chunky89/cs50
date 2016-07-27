/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

// global pointer for other functions to access the dictionary
dict d = NULL;

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
    
    d = createDictionary(); 
    FILE *fp = fopen(dictionary, "r");
    assert(fp != NULL);
    // temporary storage
    char x[LENGTH+1];
    /* assumes no word exceeds length of 45 */
    while (fscanf(fp, " %45s", x) == 1) {
        // load it to the data structure
        //x[strlen(x)] = '\0';
        int index = hash(x[0]);
        d->letter[index] = insertNode(d->letter[index], createNode(x));
        d->n++;
    }
    
    fclose(fp);

    return true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    /**
     * 0. create a duplicate of word since word pointers to a constant that cannot be modified
     * 1. convert the duplicate to lower case, make it case-insensitive, per specification
     * 2. hash the starting letter to the correct bucket(linked list)
     * 3. search in the correponding bucket
    **/
    
    char temp_dest[strlen(word)+1];
    strcpy(temp_dest, word);
    
    for(int i = 0; temp_dest[i]; i++){
        temp_dest[i] = tolower(temp_dest[i]);
    }
    
    int index = hash(temp_dest[0]);
    //printf("index = %d\n", index);
    if(searchList(d->letter[index], temp_dest))
        return true;
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    // Simply return the variable in the struct
    return d->n;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    /**
     * 0. free all the linked lists by iteration
     * 1. free the dictionary data structure
    **/ 
    for(int i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        freeList(d->letter[i]);
    }
    free(d);
    
    return true;
}

int hash(int letter)
{
    if(letter >= 'A' && letter <= 'Z')
        return letter - 'A';
    else if(letter >= 'a' && letter <= 'z')
        return letter - 'a';    
    // else return error
    return -1;
}

link createNode(const char *word)
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
    dict newDict = malloc(sizeof(struct dictNode));
    assert(newDict != NULL);
    
    // initialize the node pointers
    for(int i = 0; i<NUMBER_OF_ALPHABETS; i++)
    {
        newDict->letter[i] = NULL;
    }
    // initialize the size
    newDict->n = 0;
    
    return newDict;
}

bool searchList(link head, const char* word)
{
    link cursor = head;
    while(cursor != NULL)
    {
        if(strcmp(cursor->word, word) == 0)
            return true;
            
        cursor = cursor->next;
    }
    
    return false;
}

void freeList(link head)
{
    
    // temporary storage
    link temp;
    
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
