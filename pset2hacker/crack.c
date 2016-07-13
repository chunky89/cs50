#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LENGTH_OF_SALT 2
#define MAX_WORD_LENGTH 1024
#define MAX_PASSWORD_LENGTH 8
#define CRACKED 1
#define UNCRACKED 0


//This function calls crypt() and check whether the encrypted texts are matched
int attack(string potential_password, string salt, string encrypted);
//This function tries every word in file located in "location" using attack(...)
int searchList(FILE *f, string location, string salt, string encrypted);
//This function crack the password by trying every combination
int bruteForceAttack(string salt, string encrypted);
//Helper function of brute force routine
void incrementChar(char string[], int index);

int main(int argc, string argv[]){
    
    if (argc == 1 || argc > 2 ){
        printf("invalid input\n"); // yelling 
        return 1;    
    }
    
    if(argv[1] == NULL){
        return 1;
    }
    // get the encrypted text
    string encrypted = argv[1];
    /*the salt is the first two letters in the encrypted text
      deliberately add one more character for string terminator
    */
    char salt[LENGTH_OF_SALT+1] = {0};
    if(strlen(encrypted)!=13){
        // length of encrypted text must be 13, else return error
        return 1;
    }
    strncpy(salt, encrypted, LENGTH_OF_SALT);
    //printf("%s\n", salt);
    //printf("%d\n", attack("hello", salt, "heFw0NKyvGSTg"));
    //read_words(f);
    //string location = 
    FILE *f = NULL;
    
    printf("Cracking...\n");
    printf("Searching in dictionary...\n");
    
    if(searchList(f,"/usr/share/dict/words",salt, encrypted)){
        printf("password found in /usr/share/dict/words\n");
        return 0;
    }
    
    if(searchList(f,"/usr/share/dict/word_list.txt",salt,encrypted)){
        printf("password found in /usr/share/dict/word_list.txt\n");
        return 0;
    }
    
    printf("Searching in common password list...\n");
   
    if(searchList(f,"/usr/share/dict/common_passwords.txt",salt,encrypted)){
        printf("password found in /usr/share/dict/common_passwords.txt\n");
        return 0;
    }
    
    if(searchList(f,"/usr/share/dict/rockyou.txt",salt,encrypted)){
        printf("password found in /usr/share/dict/rockyou.txt\n");
        return 0;
    }
    printf("Crack by searching failed.\n");
    printf("Cracking...\n");
    printf("Brute force coming up...\n");
    
    if(bruteForceAttack(salt, encrypted)){
        return 0;    
    }
    
    printf("Crack by brute force failed.");
    return 0;
}

int attack(string potential_password, string salt, string encrypted){
    int ret = strcmp(crypt(potential_password, salt), encrypted);
    
    if (ret == 0){
        printf("Cracking successful!\n");
        printf("Password is: %s\n", potential_password);
        return CRACKED;
    }
    return UNCRACKED;
}

int searchList(FILE *f, string location, string salt, string encrypted){
    f = fopen(location, "r");
    char x[MAX_WORD_LENGTH];
    /* assumes no word exceeds length of 1023 */
    while (fscanf(f, " %1023s", x) == 1) {
        if(attack(x, salt, encrypted)){
            return CRACKED;
        }
    }
    //printf("No word in dictionary matches the password\n");
    fclose(f);
    return UNCRACKED;
}

// Since the strcmp function in attack() stops when it hits a null character in string, 
// A string of null characters is initialized. Then, a helpful function is created to 
// increment that string through the ASCII table as if it were a number and check each string.
int bruteForceAttack(string salt, string encrypted){
    char test[MAX_PASSWORD_LENGTH +1] = {0};

    do
    {
        // Compares until next null character
        if (attack(test, salt, encrypted) == CRACKED)
        {
            return CRACKED;
        }

        // Increment letter
        incrementChar(test, 0);
    }
    // until all combinations are tried
    while (test[MAX_PASSWORD_LENGTH] == '\0');
    
    return UNCRACKED;
}

// Function to increment character and carry over if necessary
void incrementChar(char string[], int index)  
{
    if (string[index] == '\0')
    {
        string[index] = '!';
    }
    else if (string[index] == '~')
    {
        string[index] = '!';
        incrementChar(string, index + 1);
    }
    else
    {
        string[index]++;
    }
}


