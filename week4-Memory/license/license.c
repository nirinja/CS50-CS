#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Allocate memory for plate number
        char *plate = malloc(7);

        // Copy buffer contents into plate
        strcpy(plate, buffer);

        // Save plate number in array
        plates[idx] = plate;
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
        free(plates[i]); // free memory allocated for plate number
    }

    fclose(infile);
    return 0;
}

/*The issue with the program is that all the elements in the plates array are pointing to the same buffer buffer in memory,
which is being overwritten on each iteration of the while loop.
As a result, all elements in the plates array end up pointing to the same buffer, which contains the last plate number read from the file.

To fix this issue, you need to allocate memory for each plate number in the plates array and copy the contents of buffer into it. */