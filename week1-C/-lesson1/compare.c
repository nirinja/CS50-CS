#include <cs50.h>
#include <stdio.h>

int main()
{
    int x = get_int("What's x?");
    int y = get_int("What's y?");

    if(x < y)
    {
        printf("x is lees then y\n");
    }
    else if (x > y)
    {
        printf("x is more then y \n");
    }
    else
    {
        printf("x and y are equal \n");
    }
}