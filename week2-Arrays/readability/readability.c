#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
//problem set 2-1

int getGrade(string text);
int main(void)
{
    string text = get_string("Text: ");
    int grade = getGrade(text);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    if (grade < 16 && grade > 0)
    {
        printf("Grade %i\n", grade);
    }
}

int getGrade(string text)
{
    double words = 1;
    double sentences = 0;
    double letters = 0;

    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        if ((text[i] == 46 || text[i] == 33 || text[i] == 63) && isalpha(text[i - 1])) // . or ! or ?
        {
            sentences++;
        }
        if (isblank(text[i]))
        {
            words++;
        }
    }

    // average number of letters/100 - (letters / words *100)
    double L = letters / words * 100.00;
    // average number of sentences/100 - (sentences / words * 100)
    double S = sentences / words * 100.00;
    // Coleman-Liau index
    double index = 0.0588 * L - 0.296 * S - 15.8;
    return round(index);
}