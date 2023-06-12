// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;
    int has_symbol = 0;
    int len = strlen(password);

    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i]))
        {
            has_upper = 1;
        }
        else if (islower(password[i]))
        {
            has_lower = 1;
        }
        else if (isdigit(password[i]))
        {
            has_digit = 1;
        }
        else if (ispunct(password[i]))
        {
            has_symbol = 1;
        }
    }
    if (has_upper + has_lower + has_digit + has_symbol == 4)
    {
        return true;
    }
    return false;
}
