#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define QUARTER 25
#define DIME    10
#define NICKEL  5
#define PENNY   1


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
    
    int change_in_cents = round((100*(float)n));
    // debugging
    //printf("n in float = %f\n", n*100);
    //printf("before main logic, n = %d\n", change_in_cents);
    
    // main logic
    while(change_in_cents >=QUARTER){
        change_in_cents -= QUARTER;
        numberOfQuarters +=1;
    }
    //printf("n<input, n = %d\n", change_in_cents);
    
    while(change_in_cents >= DIME && change_in_cents < QUARTER){
        change_in_cents -= DIME;
        numberOfDimes +=1;
    }
    //printf("n<QUARTER, n = %d\n", change_in_cents);
    
    while(change_in_cents >= NICKEL && n < DIME){
        change_in_cents -= NICKEL;
        numberOfNickels +=1;
    }
    //printf("n<DIME, n = %d\n", change_in_cents);
    
    while(change_in_cents >= PENNY && change_in_cents < NICKEL){
        change_in_cents -= PENNY;
        numberOfPennies +=1;
    }
    //printf("n<NICKEL, n = %d\n", change_in_cents);
    
    while(change_in_cents > 0){
        change_in_cents -= PENNY;
        numberOfPennies +=1;
        printf("11111\n");
    }
    //printf("n>0, n = %d\n", change_in_cents);
    
    /* debugging
    printf("the balance is now: %d\n", change_in_cents);
    printf("number of quarters is %d\n", numberOfQuarters);
    printf("number of dimes is %d\n", numberOfDimes);
    printf("number of nickels is %d\n", numberOfNickels);
    printf("number of pennies is %d\n", numberOfPennies);
    */
    
    printf("%d\n", numberOfQuarters + numberOfDimes + numberOfNickels + numberOfPennies);
    return 0;
}