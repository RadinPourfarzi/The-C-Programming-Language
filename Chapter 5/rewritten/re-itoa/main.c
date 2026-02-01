#include <stdio.h>
#include <string.h>

void reverse(char *source);

int main(int argc, char *argv[])
{
    char name[20] = "hello";
    reverse(name);
    printf("%s\n", name);
    return 0;
}

void itoa(int n, char *s)
{
    int sign;
    if((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    } while((n /= 10) > 0);
    if(sign < 0)
        *s++ = '-';
    *s = '\0';
}

void reverse(char *s)
{
    char *t = s;
    printf("%s\n", t);
}