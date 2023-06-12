#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    //ctype.h is quite useful library - all lowercase characters to uppercase ones.
    string s = get_string("Before: ");
    printf("After:  ");
    /*for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            //ASCII values chart: lowercase character has 32 subtracted from it
            printf("%c", s[i] - 32);
        }
        else
        {
            printf("%c", s[i]);
        }
    }*/
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}