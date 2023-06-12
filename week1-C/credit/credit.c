#include <stdio.h>
#include <cs50.h>

long Number;
bool LuhnsAlgorithm();
bool Validatio;
void Output();

int main(void)
{
    Number = get_long("Number: ");
    Validatio = LuhnsAlgorithm();
    if (Validatio)
    {
        Output();
    }
    else
    {
        printf("INVALID\n");
    }
}

bool LuhnsAlgorithm()
{
    //algorithm that determine if a credit card number is valid
    int sum1 = 0, num = 0, digits = 0, sum2 = 0;
    long number = Number;
    // every other digit (from end) * 2
    while (number > 0)
    {
        num = ((number / 10) % 10) * 2;
        while (num > 0)
        {
            digits = num % 10;
            sum1 += digits;
            num /= 10;
        }
        number /= 100;
    }

    digits = 0;
    number = Number;
    // sum of digits that weren’t multiplied by 2
    while (number > 0)
    {
        digits = number % 10;
        sum2 += digits;
        number /= 100;
    }
    Validatio = ((sum1 + sum2) % 10) == 0 ? true : false;
    return Validatio;
}

void Output()
{
    /* type of card:
    AMEX\n - 15 STRT 34 OR 37
    MASTERCARD\n - 16 STRT 51, 52, 53, 54, 55
    VISA\n - 13 OR 16 STRT 4
    INVALID\n */
    long number;
    bool inval = true;
    number = Number / 10000000000000;
    if (number == 34 || number == 37)
    {
        printf("AMEX\n");
        inval = false;
    }
    number = Number / 100000000000000;
    if (number > 50 && number < 56)
    {
        printf("MASTERCARD\n");
        inval = false;
    }
    number = Number / 1000000000000;
    if (number == 4 || number / 1000 == 4)
    {
        printf("VISA\n");
        inval = false;
    }
    if (inval)
    {
        printf("INVALID\n");
    }
}