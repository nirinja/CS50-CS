// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string input);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string input = argv[1];
        printf("%s\n", replace(input));
    }
    else
    {
        printf("Usage: ./no-vowels word\n");
    }
}

string replace(string input)
{
    string output = input;
    int n = 0;
    while (input[n] != '\0')
    {
        switch (input[n])
        {
            case 'a':
                output[n] = '6';
                break;
            case 'e':
                output[n] = '3';
                break;
            case 'i':
                output[n] = '1';
                break;
            case 'o':
                output[n] = '0';
                break;
            default:
                break;
        }
        n++;
    }
    return output;
}
