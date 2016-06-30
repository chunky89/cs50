#include <cs50.h>
#include <stdio.h>

#define MAX_CARD_LENGTH 16
#define VALID 1
#define NOT_VALID 0

void printArray(int *, int length);
//check whether a card number is valid
int validCheck(int *);
// confirm the type of card
void cardTypeCheck(int *);

int main(void){
    
    int digit[MAX_CARD_LENGTH] = {0};
    long long cardNumber;
    int i; // array index
    
    // error checking and user input
    do{
        printf("Number: ");
        cardNumber = GetLongLong();
    }
    while(cardNumber<=0);
    
    // decompose number into digits, and store it in an array
    for(i = MAX_CARD_LENGTH; cardNumber>0; i--){
        digit[i-1] = cardNumber % 10;    
        cardNumber /= 10;
    }
    // debugging
    //printf("i = %d\n", i);
    //printArray(digit, MAX_CARD_LENGTH);
    
    // check the card and print the result out
    cardTypeCheck(digit);
    
    return 0;
}

int validCheck(int *set){
    int even_digit_sum = 0;
    int odd_digit_sum = 0;
    int j = 0; // array index 
    int k = 0; // array index
    
    //probably a visa card with 13 digits (note: visa can also be 16 digits)
    if(set[0] == 0 && set[1] == 0 && set[2] == 0 && set[3] != 0){
        for(j = 4; j<= MAX_CARD_LENGTH-1; j+=2){
            // the product is double digit, decompose it to two single digits
            if(set[j]*2 - 10 >= 0){
                even_digit_sum += (set[j]*2-10) + 1;            
            }
            else {
                even_digit_sum += set[j]*2;
            }
        }
        
        for(k = 3;k<=MAX_CARD_LENGTH-1;k+=2){
            odd_digit_sum += set[k];
        }
    }
    //probably an AMEX card with 15 digits
    else if(set[0] == 0 && set[1] != 0){
        for(j = 2; j<= MAX_CARD_LENGTH-1; j+=2){
            // the product is double digit, decompose it to two single digits
            if(set[j]*2 - 10 >= 0){
                even_digit_sum += (set[j]*2-10) + 1;
                //printf("inside double digit, even sum = %d\n", even_digit_sum);
            }
            else{
                even_digit_sum += set[j]*2;
            }
            //printf("even sum = %d\n", even_digit_sum);
        }
        for(k = 1;k<=MAX_CARD_LENGTH-1;k+=2){
            odd_digit_sum += set[k];
        } 
        //printf("odd sum = %d\n", odd_digit_sum);
    }
    //probably a MasterCard or Visa card with 16 digits
    else if(set[0]!= 0){
        for(j = 0; j<= MAX_CARD_LENGTH-1; j+=2){
            // the product is double digit, decompose it to two single digits
            if(set[j]*2 - 10 >= 0){
                even_digit_sum += (set[j]*2-10) + 1;
                //printf("inside double digit, even sum = %d\n", even_digit_sum);
            }
            else{
                even_digit_sum += set[j]*2;
            }
            //printf("even sum = %d\n", even_digit_sum);
        }
        for(k = 1;k<=MAX_CARD_LENGTH-1;k+=2){
            odd_digit_sum += set[k];
        } 
        //printf("odd sum = %d\n", odd_digit_sum);        
    }
    // checking if the last digits is zero(valid)
    if((even_digit_sum + odd_digit_sum) % 10 == 0){
        return VALID;
    }
    else {
        return NOT_VALID;
    }
}

void cardTypeCheck(int *set){
        /* visa 13 or 16 digits
           AMEX 15 digits
           MasterCard 16 digits 
        */
        if(validCheck(set) == VALID){
        // 13 digits starts with 4 (must be visa)
        if(set[0] == 0 && set[1] == 0 && set[2] == 0 && set[3] == 4){
            printf("VISA\n");
        }
        // 15 digits starts with 34 or 37 (must be AMEX)
        else if(set[0] == 0 && set[1]  == 3 && (set[2] == 4 || set[2] == 7)){
            printf("AMEX\n");    
        }
        // 16 digits (could be MasterCard or Visa)
        else if(set[0]!=0){
            if(set[0] == 4){
                printf("VISA\n");
            }
            else if(set[0] == 5 && (set[1] == 1 || set[1] == 2 || set[1] == 3 || set[1] == 4 || set[1]==5)){
                printf("MASTERCARD\n");
            }
        }
    }
    else {
        printf("INVALID\n");
    }    
}

// debugging
void printArray(int *set, int length){
    int i;
    
    for(i = 0; i<length; i++){
        printf("%d ", set[i]);
    }
    printf("\n");
}