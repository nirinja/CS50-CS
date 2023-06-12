// Fails to swap two integers

#include <stdio.h>

void swap(int a, int b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(x, y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int a, int b)
{
    //problem ker se var ne zamenjata zaradi tega ker sta de
    int tmp = a;
    a = b;
    b = tmp;
}
// Notice that main and swap have two separate frames or areas of memory.
// Therefore, we cannot simply pass the values from one function to another to change them.