#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get an input from user for height of pyramid between ints of 1-8
    int Height;
    do
    {
        Height = get_int("How tall is the pyramid? ");
    }
    while (Height < 1 || Height > 8);

    // Loop for each line in Height
    for (int i = Height; i > 0; i--)
    {
        // Print the left side of hashes and spaces
        for (int j = i - 1; j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 1; k < Height - i + 2; k++)
        {
            printf("#");
        }
        // Print the middle spaces for each line
        printf("  ");
        // Print the hashes on the right side
        for (int l = 1; l < Height - i + 2; l++)
        {
            printf("#");
        }
        // Move the line down every iteration
        printf("\n");
    }
}