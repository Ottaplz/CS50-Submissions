#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // Loop by height
    for (int h = 0; h < height; h++)
    {
        // Loop by width
        for (int w = 0; w < width; w++)
        {
            // Make all non white pixels purple
            if (image[h][w].rgbtBlue == 0xff && image[h][w].rgbtGreen == 0xff && image[h][w].rgbtRed == 0xff)
            {
                image[h][w].rgbtGreen = 0x00;
                image[h][w].rgbtRed = 0x00;
                image[h][w].rgbtBlue = 0x00;
            }
            else
            {
                image[h][w].rgbtGreen = 0xff;
                image[h][w].rgbtRed = 0xff;
                image[h][w].rgbtBlue = 0x00;
            }
        }
    }
}
