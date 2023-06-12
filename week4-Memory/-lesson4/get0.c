// Gets an int from user using scanf

#include <stdio.h>

int main(void)
{
    int x;
    printf("x: ");
    //reimplement get_int
    scanf("%i", &x);
    printf("x: %i\n", x);
}
