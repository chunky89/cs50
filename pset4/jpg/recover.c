#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#define BLOCK_SIZE  512

bool isJPG(unsigned char *buf);

int main(int argc, char* argv[])
{
    // TODO
    /**
     * 1. Open memory card file
     * 2. Find the begining of jpg
     * 3. Open a new jpg
     * 4. Write 512 bytes until a new jpg is found
     * 5. Detect the end of the file
    **/
    
    // file pointer used to open and write a new jpg file
    FILE* open_jpg = NULL;
    // buffer to hold the current 512 bytes
    unsigned char temp[BLOCK_SIZE] = {0x00};
    // used to print the name of the file
    char title[sizeof("%03d.jpg")];
    // keep track of the number of jpg files found
    int curr_jpg = -1;
    
    FILE* open_raw = fopen("card.raw", "r");
    if(open_raw == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    // while it is not end of the memory card (it can still read 512 bytes)
    while(fread(temp, sizeof(char), BLOCK_SIZE, open_raw) == BLOCK_SIZE)
    {
        // find begining of a jpg file
        CONTINUE:if(isJPG(temp))
        {
            curr_jpg++;
            // first jpg found
            if(curr_jpg == 0)
            {
                sprintf(title, "%03d.jpg", curr_jpg);
                // create a new jpg file
                open_jpg = fopen(title, "w");
            }
            // not first jpg
            else
            {
                // close the previous jpg file
                fclose(open_jpg);
                sprintf(title, "%03d.jpg", curr_jpg);
                open_jpg = fopen(title, "w");
            }
            
            do
            {
                //keep writing until the next jpg found
                fwrite(temp,sizeof(char), BLOCK_SIZE, open_jpg);
                fread(temp,sizeof(char), BLOCK_SIZE, open_raw);
            }
            while(!isJPG(temp) && !feof(open_raw));

            /**when the last JPG is written, the end of file is reached, 
             * the while loop quits, then it goto CONTINUE label, it tests whether
             * the current block has JPG signiture, return false, then the if quits,
             * and the control goes back to the outest while, test whether the fread still
             * read full block (512 bytes), it will return false (since the end of file is reached),
             * then the outest while loop quits, program ends.
            **/
            goto CONTINUE;
        }
        //else go back to while and keep reading
    }
    fclose(open_raw);
    return 0;
}

/**
 * this function checks whether a block is a JPG signiture,
 * return true if it is, false otherwise.
**/
bool isJPG(unsigned char *buf)
{
    if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff)
    {
        // 0xE0 = 224 in decimal
        // 0xEF = 239 in decimal
        if(buf[3]>= 224 && buf[3] <= 239)
        {
            return true;
        } 
    }
    return false;
}
