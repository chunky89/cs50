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
    
    /*
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    */

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
    //RGBTRIPLE temp[bi.biWidth*factor + new_padding];
    int index = 0;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        RGBTRIPLE *temp = malloc(sizeof(RGBTRIPLE)*(bi.biWidth*factor + new_padding));
        
        // iterate over pixels in scanline
        index = 0;
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int k = 0; k < factor; k++){
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                temp[index] = triple;
                index++;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < new_padding; k++)
        {
            temp[index].rgbtBlue = 0x00;
            temp[index].rgbtGreen = 0x00;
            temp[index].rgbtRed = 0x00;
            fputc(0x00, outptr);
            index++;
        }
        
        for(int g = 0; g < factor; g++){
            fwrite(&temp, sizeof(RGBTRIPLE), 1, outptr);
        }
        free(temp);
    }
    
    /**
     * need to write four things:
     * 1. bfSize: length of headers(file header 14 bytes, info header 40 bytes) + biSizeImage(image size + padding)
     * 2. biWidth: new width
     * 3. biHeight: new height
     * 4. biSizeImage: new width * new height * biBicount(3 bytes per pixel)
    **/
    
    new_bi.biWidth = bi.biWidth * factor;
    new_bi.biHeight = bi.biHeight * factor;
    new_bi.biSizeImage = new_bi.biWidth * new_bi.biHeight * new_bi.biBitCount + new_padding * new_bi.biWidth;
    new_bf.bfSize = 14 + 40 + new_bi.biSizeImage;
    // write outfile's BITMAPINFOHEADER
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}