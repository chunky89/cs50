/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize a BMP piece by piece, by a factor of n, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atoi(argv[1]);
    if(factor < 1 || factor > 100)
        return 1;
    
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // get a copy of original file header
    BITMAPFILEHEADER new_bf = bf;
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    // get a copy of original info header
    BITMAPINFOHEADER new_bi = bi;
    
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    

    /**
     * need to write four things:
     * 1. bfSize
     * 2. biWidth: new width
     * 3. biHeight: new height
     * 4. biSizeImage
    **/
    
    // // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
    
    new_bi.biWidth = bi.biWidth * factor;
    new_bi.biHeight = bi.biHeight * factor;
    new_bi.biSizeImage = (sizeof(RGBTRIPLE)*new_bi.biWidth + new_padding)*abs(new_bi.biHeight);
    new_bf.bfSize = bf.bfSize - bi.biSizeImage + new_bi.biSizeImage;
    
    /**
     * Must write the file header first, then info header, 
     * because it is how they are located in bmp file. Previous
     * mistake, write it at the end of the main function.
    **/
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        for(int j = 0; j < factor; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for(int l = 0; l < factor; l++){
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            // move the cursor back to the beginning of the scanline
            if (j < factor - 1)
                // only move the cursor factor -1 times
                fseek(inptr,-(padding + sizeof(RGBTRIPLE)*bi.biWidth), SEEK_CUR);
        }
        
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}