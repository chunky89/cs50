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
// DES encrypted text will always be length of 13
#define LENGTH_OF_ENCRYPTED_TEXT 13


int letterCounter[8];
char validCharacters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%^&*()_+[]{}:;<>,./?'";
char bruteString[9];  // One more to null terminate.

//This function calls crypt() and check whether the encrypted texts are matched
int attack(string potential_password, string salt, string encrypted);
//This function tries every word in file located in "location" using attack(...)
int searchList(FILE *f, string location, string salt, string encrypted);
//This function crack the password by trying every combination
int bruteForceAttack(string salt, string encrypted);

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
    if(strlen(encrypted)!= LENGTH_OF_ENCRYPTED_TEXT){
        // length of encrypted text must be 13, else return error
        return 1;
    }
    strncpy(salt, encrypted, LENGTH_OF_SALT);
    /* debugging */
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

    if(bruteForceAttack(salt, encrypted) == true){
        return 0;    
    }
    
    printf("Crack by brute force failed.\n");
    return 0;
}

int attack(string potential_password, string salt, string encrypted){
    int ret = strcmp(crypt(potential_password, salt), encrypted);
    
    if (ret == 0){
        printf("Cracking successful!\n");
        printf("Password is: %s\n", potential_password);
        return true;
    }
    return false;
}

int searchList(FILE *f, string location, string salt, string encrypted){
    f = fopen(location, "r");
    char x[MAX_WORD_LENGTH];
    /* assumes no word exceeds length of 1023 */
    while (fscanf(f, " %1023s", x) == 1) {
        if(attack(x, salt, encrypted)){
            return true;
        }
    }
    //printf("No word in dictionary matches the password\n");
    fclose(f);
    return false;
}

int bruteForceAttack(string salt, string encrypted){
    //char arr_chars[] = {"0123456789abcdefghijklmnopqrstuvwxyz"};
    char arr_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%^&*()_+[]{}:;<>,./?'";
    
    int arr_length = strlen(arr_chars);
    
    // one more place to null terminate
    char cur_word[MAX_PASSWORD_LENGTH + 1] = {0};
    //cur_word[MAX_PASSWORD_LENGTH] = '\0'; 
    // use an array of 8 integers instead of eight separate integers for index value 
    int pos[MAX_PASSWORD_LENGTH];
    
    // Outer loop - controls word length
    for (int max_chars = 0; max_chars < MAX_PASSWORD_LENGTH; max_chars++)
    {
        printf("Trying potential passwords with length %d\n", max_chars + 1);
        
        // flag value for main brute force loop
        bool loop_completed = false;
        
        // Initialize the word
        int idx;
        
        for (idx = 0; idx <= max_chars; idx++)
        {
            pos[idx] = 0;
            cur_word[idx] = arr_chars[pos[idx]];
        }
        
        cur_word[idx] = '\0';
    
        // Main brute-force loop
        // Ends when every symbol combination is checked
        while (!loop_completed)
        {
            // Try current word
            if (attack(cur_word, salt, encrypted))
                return true;
        
            // One iteration of brute-force
            bool shift = true;
            
            for (int cur_char = 0; cur_char <= max_chars; cur_char++)
                // If shift - change character
                if (shift)
                {
                    // If all character are done
                    if (pos[cur_char] == arr_length - 1)
                    {
                        // If last symbol - loop is over
                        if (cur_char == max_chars)
                            loop_completed = true;
                        // Change to first symbol again
                        else
                        {
                            pos[cur_char] = 0;
                            cur_word[cur_char] = arr_chars[pos[cur_char]];
                        }
                    }
                    else
                    {
                        cur_word[cur_char] = arr_chars[++pos[cur_char]];
                        
                        shift = false;
                    }
                }
        }
    }
    
    return false;
}


