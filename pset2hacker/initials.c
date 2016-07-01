#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void){
    string s = GetString();
    
    if(isalpha(s[0])){
        printf("%c", toupper(s[0]));
        //printf("11111\n");
    }
    
    // Be careful about the boundary
    // When n = strlen(s), no next character whatsoever
    for(int i = 0, n = strlen(s)-1; i<n; i++){
        if(s[i] == ' ' && s[i+1] == ' '){
            //printf("%d\n", i);
        }
        else if(s[i] == ' ' && s[i+1] != ' '){
            printf("%c", toupper(s[i+1]));
        }
    }
    printf("\n");
    
    return 0;
}