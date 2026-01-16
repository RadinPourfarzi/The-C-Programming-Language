#include <stdio.h>

int lower(int character);

int main(void)
{
    int c;

    if((c = getchar()) != EOF)
        putchar(lower(c));

    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}