// Prints an integer's address

#include <stdio.h>

int main(void)
{
    int n = 50;
    printf("%p\n", &n);
    //Notice the %p, which allows us to view the address of a location in memory.
    //&n can be literally translated as “the address of n.”
}
