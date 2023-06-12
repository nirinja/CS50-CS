#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        //1st section
        for (int j = 0; j < (height - i); j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        //space section
        printf("  ");

        //2nd section
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //new line
        printf("\n");
    }
}