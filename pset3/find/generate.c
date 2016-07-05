/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    /*
    This if statement checks the command line argument is not 2 and 3,
    making sure that the program can be executed normally.
    Otherwise, throw user a message for correct usage and return with ERROR.
    */
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // this line converts the string argv[1] to an int 
    int n = atoi(argv[1]);

    /*
    If there are 3 command line arguments, meaning the optional
    argument has been hit. We need to "seed" the random number
    using the "number" (after atoi) entered by users.
    
    Otherwise, argc = 2. (no seed is required)it generates the random number for 
    "seed" from 0 to current calendar time. Since the time is always changing, 
    meaning that the seed will be different, resulting the following drand(48) 
    (seeding random number is different).
    */
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // generate 10 seed random numbers
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}