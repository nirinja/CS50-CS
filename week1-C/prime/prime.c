#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int min = get_int("Minimum: ");
    int max = get_int("Maximum: ");

    while (min < max)
    {
        int prime = 1;
        for (int i = 2; i < min; i++)
        {
            if ((min % i) == 0)
            {
                prime = 0;
            }
        }
        if (prime == 1 && min != 1)
        {
            printf("%i\n", min);
        }
        min++;
    }
}
