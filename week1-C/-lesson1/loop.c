#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int a = get_int("Nmber of meows:");
    for (int i = 0; i < a; i++)
    {
        printf("meow\n");
    }
}