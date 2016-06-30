#include <cs50.h>
#include <stdio.h>

#define QUARTER 0.25
#define DIME    0.10
#define NICKEL  0.05
#define PENNY   0.01


int main(void){
    
    
    // counters
    int numberOfQuarters = 0;
    int numberOfDimes = 0;
    int numberOfNickels = 0;
    int numberOfPennies = 0;
    
    // error checking
    float n;
    do{
        printf("O hai! How much change is owed?\n");
        n = GetFloat();
    }
    while(n<0);
    
    // main logic
    while(n >=QUARTER && n <= n){
        n -= QUARTER;
        numberOfQuarters +=1;
    }
    
    while(n >= DIME && n <= QUARTER){
        n -= DIME;
        numberOfDimes +=1;
    }
    
    while(n >= NICKEL && n <= DIME){
        n -= NICKEL;
        numberOfNickels +=1;
    }
    
    while(n >= PENNY && n <= NICKEL){
        n -= PENNY;
        numberOfPennies +=1;
    }
    
    while(n>0){
        n -= PENNY;
        numberOfPennies +=1;
    }
    
    /* debugging
    printf("the balance is now: %f\n", n);
    printf("number of quarters is %d\n", numberOfQuarters);
    printf("number of dimes is %d\n", numberOfDimes);
    printf("number of nickels is %d\n", numberOfNickels);
    printf("number of pennies is %d\n", numberOfPennies);
    */
    
    printf("%d\n", numberOfQuarters + numberOfDimes + numberOfNickels + numberOfPennies);
    return 0;
}