// Copies a BMP file
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }

    // Update bitmap height to flip the image
    bi.biHeight = -bi.biHeight;

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Allocate memory for a scanline
    RGBTRIPLE *scanline = malloc(bi.biWidth * sizeof(RGBTRIPLE));
    if (scanline == NULL)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Not enough memory to process file.\n");
        return 5;
    }

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) //the "abs" function is used to calculate the absolute value of a number. (int abs(int x);)
    {
        // Read a scanline from infile
        fread(scanline, sizeof(RGBTRIPLE), bi.biWidth, inptr);

        // Write the scanline to outfile in reverse order
        for (int j = bi.biWidth - 1; j >= 0; j--)
        {
            fwrite(&scanline[j], sizeof(RGBTRIPLE), 1, outptr);
        }

        // Add padding to outfile, if any
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for scanline
    free(scanline);

    // Close infile & outfile
    fclose(inptr);
    fclose(outptr);

    // Success
    return 0;
}
