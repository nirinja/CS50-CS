// Capitalizes a copy of a string, defining n in loop too
//create an authentic copy of our string

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Get a string
    char *s = get_string("s: ");

    // Allocate memory for another string
    // creates a block of memory that is the length of the string s plus one. This allows for the inclusion of the null \0 character in our final, copied string
    char *t = malloc(strlen(s) + 1);

    // Copy string into memory, including '\0'
    // It’s best not to call unneeded functions in the middle condition of the for loop, as it will run over and over again.
    //When moving n = strlen(s) to the left-hand side, the function strlen only runs once.
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    // Capitalize copy
    t[0] = toupper(t[0]);

    // Print strings
    printf("s: %s\n", s);
    printf("t: %s\n", t);
}
