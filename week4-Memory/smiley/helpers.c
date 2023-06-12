#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Change all black pixels to a color of your choosing
void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    //rainbow color array
    RGBTRIPLE colors[] =
    {
        {255, 0, 0},   // Red
        {255, 127, 0}, // Orange
        {255, 255, 0}, // Yellow
        {0, 255, 0},   // Green
        {0, 0, 255},   // Blue
        {75, 0, 130},  // Indigo
        {148, 0, 211}  // Violet
    };
    int num_colors = sizeof(colors) / sizeof(RGBTRIPLE);

    // loop through pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if pixel is black
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Calculate a rainbow color index based on the pixel position
                int color_index = (i + j) % num_colors;
                // pixel color = rainbow color
                image[i][j] = colors[color_index];
            }
        }
    }
}

/*
STAFF SOLUTION:
#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Make black pixels turn red
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtRed = 0xff;
            }
        }
    }
}*/