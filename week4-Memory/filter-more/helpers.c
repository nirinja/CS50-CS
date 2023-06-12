#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int brightness = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            double toRound = brightness / 3.0;
            brightness = (int)round(toRound);
            // Check if pixel is black
            image[i][j].rgbtRed = brightness;
            image[i][j].rgbtGreen = brightness;
            image[i][j].rgbtBlue = brightness;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int rj = width - j - 1;
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][rj];
            image[i][rj] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];

    // Iterate through each pixel in the image
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int count = 0;
            int red = 0, green = 0, blue = 0;

            // Iterate through each neighboring pixel in a 3x3 kernel
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // Calculate the row and column indices of the neighboring pixel
                    int neighbor_row = row + i;
                    int neighbor_col = col + j;

                    // Check if the neighboring pixel is within the bounds of the image
                    if (neighbor_row >= 0 && neighbor_row < height && neighbor_col >= 0 && neighbor_col < width)
                    {
                        // Add the color values of the neighboring pixel to the running sum
                        red += image[neighbor_row][neighbor_col].rgbtRed;
                        green += image[neighbor_row][neighbor_col].rgbtGreen;
                        blue += image[neighbor_row][neighbor_col].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values of the neighboring pixels
            blurred[row][col].rgbtRed = round((float)red / count);
            blurred[row][col].rgbtGreen = round((float)green / count);
            blurred[row][col].rgbtBlue = round((float)blue / count);
        }
    }

    // Copy the blurred image back into the original image array
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = blurred[row][col];
        }
    }
}

// Detect edges
int rSobelX = 0;
int gSobelX = 0;
int bSobelX = 0;
int rSobelY = 0;
int gSobelY = 0;
int bSobelY = 0;
int wd = 0;
int hi = 0;
RGBTRIPLE edge[514][514];

void Sobel(int kGx, int kGy, int row, int col)
{
    if (!(row >= 0 && row < hi && col >= 0 && col < wd))
    {
        return;
    }

    rSobelX += kGx * edge[row][col].rgbtRed;
    gSobelX += kGx * edge[row][col].rgbtGreen;
    bSobelX += kGx * edge[row][col].rgbtBlue;

    rSobelY += kGy * edge[row][col].rgbtRed;
    gSobelY += kGy * edge[row][col].rgbtGreen;
    bSobelY += kGy * edge[row][col].rgbtBlue;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    wd = width;
    hi = height;

    // Copy the image to the edge array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edge[i][j] = image[i][j];
        }
    }

    // Create temporary array to store edge image
    RGBTRIPLE edge_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // px1
            Sobel(-1, -1, i + 1, j - 1);
            // px2
            Sobel(0, -2, i + 1, j);
            // px3
            Sobel(1, -1, i + 1, j + 1);
            // px4
            Sobel(-2, 0, i, j - 1);
            // px5
            Sobel(0, 0, i, j);
            // px6
            Sobel(2, 0, i, j + 1);
            // px7
            Sobel(-1, 1, i - 1, j - 1);
            // px8
            Sobel(0, 2, i - 1, j);
            // px9
            Sobel(1, 1, i - 1, j + 1);

            // Calculate the magnitude of the Sobel operator
            int magnitudeR = round(sqrt(pow(rSobelX, 2) + pow(rSobelY, 2)));
            int magnitudeG = round(sqrt(pow(gSobelX, 2) + pow(gSobelY, 2)));
            int magnitudeB = round(sqrt(pow(bSobelX, 2) + pow(bSobelY, 2)));
            int magnitude = round((magnitudeR + magnitudeG + magnitudeB) / 3.0);

            // Truncate the magnitude at 255 and set it as the edge pixel value
            edge_image[i][j].rgbtRed = fmin(255, magnitudeR);
            edge_image[i][j].rgbtGreen = fmin(255, magnitudeG);
            edge_image[i][j].rgbtBlue = fmin(255, magnitudeB);

            // Reset Sobel values
            rSobelX = 0;
            gSobelX = 0;
            bSobelX = 0;
            rSobelY = 0;
            gSobelY = 0;
            bSobelY = 0;
        }
    }

    // Copy the edge image back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edge_image[i][j];
        }
    }
    return;
}
/*
How to interpret these kernels? In short, for each of the three color values for each pixel, we’ll compute two values Gx and Gy.
 To compute Gx for the red channel value of a pixel, for instance, we’ll take the original red values for the nine pixels that form a 3x3 box around the pixel,
  multiply them each by the corresponding value in the Gx kernel, and take the sum of the resulting values.

Why these particular values for the kernel? In the Gx direction, for instance, we’re multiplying the pixels to the right of the target pixel by a positive number,
 and multiplying the pixels to the left of the target pixel by a negative number. When we take the sum, if the pixels on the right are a similar color to the pixels on the left,
 the result will be close to 0 (the numbers cancel out). But if the pixels on the right are very different from the pixels on the left, then the resulting value will be very positive or
 very negative, indicating a change in color that likely is the result of a boundary between objects. And a similar argument holds true for calculating edges in the y direction.

Using these kernels, we can generate a Gx and Gy value for each of the red, green, and blue channels for a pixel. But each channel can only take on one value, not two:
so we need some way to combine Gx and Gy into a single value. The Sobel filter algorithm combines Gx and Gy into a final value by calculating the square root of Gx^2 + Gy^2.
 And since channel values can only take on integer values from 0 to 255, be sure the resulting value is rounded to the nearest integer and capped at 255!

And what about handling pixels at the edge, or in the corner of the image? There are many ways to handle pixels at the edge, but
for the purposes of this problem, we’ll ask you to treat the image as if there was a 1 pixel solid black border around the edge of the image:
therefore, trying to access a pixel past the edge of the image should be treated as a solid black pixel (values of 0 for each of red, green, and blue).
 This will effectively ignore those pixels from our calculations of Gx and Gy. */