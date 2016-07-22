/**
 * test.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Print useful information about a bmp file.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./copy infile\n");
        return 1;
    }

    // remember filenames
    //int factor = atoi(argv[1]);
    char* infile = argv[1];
    //char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    printf("bf.bfType = %d\n", bf.bfType);
    printf("bf.bfSize = %d\n", bf.bfSize);
    //read infile's BITMAPINFOHEADER
    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    printf("bi.biSize = %d\n", bi.biSize);
    printf("bi.Width = %d\n", bi.biWidth);
    printf("bi.Height = %d\n", bi.biHeight);
    printf("bi.biBitCount = %d\n", bi.biBitCount);
    printf("bi.biSizeImage = %d\n", bi.biSizeImage);

    // close infile
    fclose(inptr);
    // that's all folks
    return 0;
}
