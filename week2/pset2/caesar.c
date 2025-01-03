#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Only accept a single CLI
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check each char of argv[1] to ensure all numeric
    int n = strlen(argv[1]);

    for (int i = 0; i < n; i++)
        if (isdigit(argv[1][i]))
        {
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }


    // Get plaintext from user
    string text = get_string("plaintext:  ");

    // Defining strlen of text and converting argv[1] to an int
    int len = strlen(text);
    int k = atoi(argv[1]);

    //Rotational function that checks only alphabetical characters and rotates based on k
    for (int i = 0; i < len; i++)
        if isalpha(text[i])
        {
            if isupper(text[i])
            {
                text[i] = (((text[i] - 'A') + k)%26 + 'A');
            }
            else
            {
                text[i] = (((text[i] - 'a') + k)%26 + 'a');
            }
        }

    // Print out the rotated plaintext into ciphertxt
    printf("ciphertext: %s\n", text);
}
