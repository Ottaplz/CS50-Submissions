#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Add all values together and average them
            double sum = round(image[h][w].rgbtGreen + image[h][w].rgbtBlue + image[h][w].rgbtRed);
            double average = round(sum / 3.0);
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue  = average;
            image[h][w].rgbtRed  = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Calculate individual pixels with sepia equation
            // Set temporary variables for RGB then reassign once calculations finish
            int Green = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen  + .168 * image[h][w].rgbtBlue);
            int Blue  = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen  + .131 * image[h][w].rgbtBlue);
            int Red  = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen  + .189 * image[h][w].rgbtBlue);
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }
            image[h][w].rgbtRed = Red;
            image[h][w].rgbtGreen = Green;
            image[h][w].rgbtBlue = Blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h <= height - 1; h++)
    {
        // Set half as value
        int half = round((width / 2.0) - 1);
        // Swap all of the pixels horizontally
        for (int w = 0; w <= half; w++)
        {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][(width - 1) - w];
            image[h][(width - 1) - w] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Setting a copy of image to manipulate in function without effecting image values
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Implementing variables
    int counter = 0;
    int red = 0;
    int blue = 0;
    int green = 0;
    // Loop by Height and Width
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Loop to check all pixels adjacent to current [hj][w]
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {
                    // Conditional to make sure the pixel exists
                    if (i >= 0 && j >= 0 && i < height && j < width)
                    {
                        // Add counter to use for average calculation, sum all of the values for each valid pixel
                        counter++;
                        green += copy[i][j].rgbtGreen;
                        blue += copy[i][j].rgbtBlue;
                        red += copy[i][j].rgbtRed;
                    }
                }
            }
            // Assign original image the averaged amount of all valid adjacent pixels
            image[h][w].rgbtGreen = round((float)green / counter);
            image[h][w].rgbtBlue = round((float)blue / counter);
            image[h][w].rgbtRed = round((float)red / counter);
            // Reset variable for next pixel
            green = 0;
            blue = 0;
            red = 0;
            counter = 0;
        }
    }
    return;
}
