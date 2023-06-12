// Dangerously gets a string from user using scanf

#include <stdio.h>

int main(void)
{
    //a string larger than 4 would create an error.
    char s[4];
    printf("s: ");
    // reimplement get_string
    scanf("%s", s);
    printf("s: %s\n", s);
    //no & is required because strings are special.
}
