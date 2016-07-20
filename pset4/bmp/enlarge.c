#include <stdio.h>
#include <stdlib.h>

/**
 * copyArray.c
 *
 * Computer Science 50
 * Problem Set 4 practice
 *
 * Enlarge a matrix by a factor of n, piece by piece, just because.
 */

int main(int argc, char* argv[])
{
    //ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./enlarge infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];
    //int x[10] = {1,2,3,4,5,6,5000,6,-10,11};
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w+");
    
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    //fwrite(x, sizeof(int), 10 , outptr);
    // write outfile's BITMAPFILEHEADER
    //fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    //fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    //int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //int temp = 0;
    // iterate over infile's scanlines
    
    for (int i = 0; i < 1; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < 5; j++)
        {
            // temporary storage
            int temp;

            // read RGB triple from infile
            fread(&temp, sizeof(int), 1, inptr);
            printf("temp = %d\n", (int)temp);
            // write RGB triple to outfile
            fwrite(&temp, sizeof(int), 1, outptr);
            
            //printf("temp = %d\n", temp);
        }

        // skip over padding, if any
        //fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        // for (int k = 0; k < padding; k++)
        // {
        //     fputc(0x00, outptr);
        // }
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    

    // that's all folks
    return 0;
}