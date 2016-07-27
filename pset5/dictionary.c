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

// global pointer for other function to access the dictionary
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
        x[strlen(x)] = '\0';
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
    //dict d_for_check = d;
    
    char temp_dest[strlen(word)+1];
    strcpy(temp_dest, word);
    
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
    return d->n;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    //dict d_for_unload = d;
    
    for(int i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        freeList(d->letter[i]);
    }
    free(d);
    
    return true;
    //return false;
}

int hash(int letter)
{
    if(letter >= 'A' && letter <= 'Z')
        return letter - 'A';
    else if(letter >= 'a' && letter <= 'z')
        return letter - 'a';    

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
    d = malloc(sizeof(struct dictNode));
    assert(d != NULL);
    
    // initialize the node pointers
    for(int i = 0; i<NUMBER_OF_ALPHABETS; i++)
    {
        d->letter[i] = NULL;
    }
    // initialize the size
    d->n = 0;
    
    return d;
}

bool searchList(link head, const char* word)
{
    // bug bug bug!!!!!
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
