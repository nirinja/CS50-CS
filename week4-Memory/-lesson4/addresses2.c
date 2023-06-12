// Stores and prints an integer's address

#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
   //&n can be literally translated as “the address of n.”
   //*A pointer is a variable that contains the address of some value
   //p is a pointer that contains a number that is the address of an integer n
    printf("%p\n", p);
}
