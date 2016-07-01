#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// caesar encrypt method for single character
int caesarEncrypt(int in_text, int key);
void printOutputMessage(string, int length);

int main(int argc, string argv[]){
    if (argc == 1 || argc > 2){
        printf("invalid input\n"); // yelling 
        return 1;    
    }
    // validate the key
    for(int index = 0, length = strlen(argv[1]); index < length; index++){
        if(isalpha(argv[1][index]) == 0){
            printf("Keyword must only contain letters A-Z and a-z\n"); // yelling
            //printf("%c\n", argv[1][index]);
            return 1;
        }
    }
    
    // get the key
    string k = argv[1];
    
    // get the input text
    string in_text = GetString();
    
    
    int i; // for input text
    int j = 0; // for keyword
    int n;
    
    for(i = 0, n = strlen(in_text); i<n; i++){
        j = j % strlen(k);
        //printf("j = %d\n", j);
        //printf("%d\n", k[j]-'a');
        
        if(isalpha(in_text[i])){
            if(isupper(k[j])){
                in_text[i] = caesarEncrypt(in_text[i], k[j]-'A');
            }
            else{
                in_text[i] = caesarEncrypt(in_text[i], k[j]-'a');
            }
            j++;
        }
    }
    
   
    printOutputMessage(in_text, strlen(in_text));
    //printf("%c\n", caesarEncrypt(' ',20));
}

int caesarEncrypt(int in_text, int key){
    
    //lower case letter
    if(in_text>='a' && in_text<='z'){
        if(in_text + key >'z'){
            in_text = 'a'+ (key-('z'-in_text+1));
            //printf("out of boundary %c\n", in_text[i]);
        }
        else {
            in_text = in_text + key; 
            //printf("within boundary %c\n", in_text[i]);
        }
            
    }
    //upper case letter
    else if(in_text>='A' && in_text<='Z'){
        if(in_text+key >'Z'){
            in_text = 'A'+ (key-('Z'-in_text+1));
        }
        else {
            in_text = in_text + key;    
        }
    }
    
    return in_text;
}

void printOutputMessage(string out_text, int length){
    int i;
    for(i = 0; i<length; i++){
        printf("%c", out_text[i]);
    }
    printf("\n");    
}