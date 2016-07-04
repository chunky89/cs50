#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect number of parameters\n");
        
        return 1;
    }
    string password = argv[1];
    string encrypted_password = crypt(password, "he");
    
    printf("encryption is finished: %s\n", encrypted_password);
    return 0;
}