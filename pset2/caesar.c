#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LETTERS 26

int main(int argc, string argv[]){
    if (argc == 1 || argc > 2 ){
        printf("invalid input\n"); // yelling 
        return 1;    
    }
    int k = atoi(argv[1]);
    //printf("%d\n",k);
    string in_text = GetString();
    int i;
    int n;
    
    // periodic calculations
    while (k > MAX_LETTERS){
        k -= MAX_LETTERS;    
    }
    for(i = 0, n = strlen(in_text); i<n; i++){
        //lower case letter
        if(in_text[i]>='a' && in_text[i]<='z'){
            if(in_text[i] + k >'z'){
                in_text[i] = 'a'+ (k-('z'-in_text[i]+1));
                //printf("out of boundary %c\n", in_text[i]);
            }
            else {
                in_text[i] = in_text[i] + k; 
                //printf("within boundary %c\n", in_text[i]);
            }
            
        }
        
        //upper case letter
        
        else if(in_text[i]>='A' && in_text[i]<='Z'){
            if(in_text[i]+k >'Z'){
                in_text[i] = 'A'+ (k-('Z'-in_text[i]+1));
            }
            else {
                in_text[i] = in_text[i] + k;    
            }
        }
        
    }
    
    for(i = 0, n = strlen(in_text); i<n; i++){
        printf("%c", in_text[i]);
    }
    printf("\n");
    
    return 0;
}