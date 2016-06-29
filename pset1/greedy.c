#include <cs50.h>
#include <stdio.h>

#define QUARTER 0.25
#define DIME    0.10
#define NICKEL  0.05
#define PENNY   0.01


int main(void){
    float n;
    // error checking
    do{
        printf("O hai! How much change is owed?\n");
        n = GetFloat();
    }
    while(n<0);
    
    
    return 0;
}