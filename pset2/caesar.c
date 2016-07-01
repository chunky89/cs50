#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LETTERS 26

void encrypt(string, int key);
void printOutputMessage(string, int length);

int main(int argc, string argv[]){
    if (argc == 1 || argc > 2 ){
        printf("invalid input\n"); // yelling 
        return 1;    
    }
    // get the key
    int k = atoi(argv[1]);
    //printf("%d\n",k);
    string in_text = GetString();
    
    // periodic calculations
    while (k > MAX_LETTERS){
        k -= MAX_LETTERS;    
    }

    encrypt(in_text,k);
    printOutputMessage(in_text, strlen(in_text));
    
    return 0;
}

void encrypt(string in_text, int key){
    int i;
    int n;
    for(i = 0, n = strlen(in_text); i<n; i++){
    //lower case letter
        if(in_text[i]>='a' && in_text[i]<='z'){
            if(in_text[i] + key >'z'){
                in_text[i] = 'a'+ (key-('z'-in_text[i]+1));
                //printf("out of boundary %c\n", in_text[i]);
            }
            else {
                in_text[i] = in_text[i] + key; 
                //printf("within boundary %c\n", in_text[i]);
            }
            
        }
        
        //upper case letter
        else if(in_text[i]>='A' && in_text[i]<='Z'){
            if(in_text[i]+key >'Z'){
                in_text[i] = 'A'+ (key-('Z'-in_text[i]+1));
            }
            else {
                in_text[i] = in_text[i] + key;    
            }
        }
        
    } 
}

void printOutputMessage(string out_text, int length){
    int i;
    for(i = 0; i<length; i++){
        printf("%c", out_text[i]);
    }
    printf("\n");    
}

