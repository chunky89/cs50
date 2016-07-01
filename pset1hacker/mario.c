#include <cs50.h>
#include <stdio.h>

#define GAP 2

void print(int n, char s);

int main(void){
    
    int n;
    int i = 0, j = 0;
    // error checking
    do
    {
        printf("Height: ");
        n = GetInt();
    }
    while(n<0 || n>23);
    
    j = n;
    for(i = 1; i<=n; i++){
        print(j-1,'b');
        print(i,'h');
        print(GAP, 'b');
        print(i,'h');
        //print(j-1,'b');
        printf("\n");
        j--;
    }
    
    return 0;
}

void print(int n, char s){
    int i = 0;
    for(i = 0; i<n; i++){
        // print n hash symbols
        if (s == 'h'){
            printf("#");
        }
        // print n blank space symbols
        else if(s == 'b'){
            printf(" ");
        }
    }
}