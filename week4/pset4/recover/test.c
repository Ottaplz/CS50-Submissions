#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int signature[] = {0xff, 0xd8, 0xff, 0xe0};
int BLOCK_SIZE = 512;
int JPEG = 0;
int BLOCK = 0;
typedef uint8_t BYTE;


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
}