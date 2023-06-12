#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open the forensic image file- wasted space on disk is called “slack space.”
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // Initialize variables
    unsigned char buffer[512];
    int file_count = 0;
    char filename[8];
    FILE *outfile = NULL;

    // Iterate over the forensic image file
    while (fread(buffer, sizeof(buffer), 1, file) == 1)
    {
        // Check for JPEG signature -0xff, 0xd8, 0xff, fourth byte’s first four bits are 1110
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous JPEG file (if any)
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // Create a new JPEG file
            sprintf(filename, "%03i.jpg", file_count);
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                fclose(file);
                printf("Could not create file\n");
                return 1;
            }

            // Write the buffer to the new JPEG file
            fwrite(buffer, sizeof(buffer), 1, outfile);

            // Increment the file count
            file_count++;
        }
        else
        {
            // Write the buffer to the current JPEG file (if any)
            if (outfile != NULL)
            {
                fwrite(buffer, sizeof(buffer), 1, outfile);
            }
        }
    }

    // Close the last JPEG file (if any)
    if (outfile != NULL)
    {
        fclose(outfile);
    }

    // Close the forensic image file
    fclose(file);

    // Success
    return 0;
}
