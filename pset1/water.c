#include <cs50.h>
#include <stdio.h>

#define BOTTLE_PER_MIN 12

int main(void){
    printf("minutes: ");
    int duration = GetInt();
    printf("bottles: %d\n",BOTTLE_PER_MIN*duration);
    return 0;
}