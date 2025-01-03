#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int signature[] = {0xff, 0xd8, 0xff, 0xe0};
int BLOCK_SIZE = 512;
int JPEG = -1;
typedef uint8_t BYTE;
FILE *img = 0;


int main(int argc, char *argv[])
{
    // Ensure only one CLA
    if (argc != 2)
    {
        printf("Proper usage: ./recover *FILE*\n");
        return 1;
    }

    // Check whether or not file exists
    string filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    BYTE buffer[BLOCK_SIZE];

    // Loop to check each block of 512 BYTES
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Variable to track signature match
        int total = 0;

        // Loop to check signature
        for (int i = 0; i < 4; i++)
        {
            // Check to see if final Byte matches any of the 16 options
            if (i == 3)
            {
                for (int j = 0; j < 15; j++)
                {
                    if (buffer[i] == signature[i] + j)
                    {
                        total++;
                        break;
                    }
                }
            }
            // Check to see if the first 3 bytes match signature
            else if (buffer[i] == signature[i])
            {
                total++;
            }
        }

        // Write to Newly created address in memory
        // If signature matches a jpeg
        if (total == 4)
        {
            JPEG++;
            char *address = malloc(8 * sizeof(char));
            if (address == NULL)
            {
                return 1;
            }

            sprintf(address, "%03i.jpg", JPEG);

            // Open Newly created Address in memory
            if (JPEG == 0)
            {
                img = fopen(address, "w");
            }

            // Close previous file and open new file to write into
            else
            {
                fclose(img);
                img = fopen(address, "w");
            }
            free(address);
        }

        // Writing the data from buffer into opened file
        if (JPEG >= 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }

    }
    // Close all open files and free memory
    fclose(img);
    fclose(file);
}



