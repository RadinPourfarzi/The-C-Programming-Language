#include <stdio.h>
#include <string.h>

extern void reverse(char *s);
void itoa(int n, char *s);

int main(int argc, char *argv[])
{
    char values[1000];
    int num = 12345;
    itoa(num, values);
    printf("%s\t%d\n", values, num);
    return 0;
}
void itoa(int n, char *s)
{
    int sign;
    char *head = s;
    if((sign = n) < 0)
        n = -n;
    do {
        *s++ = n % 10 + '0';
    } while((n /= 10) > 0);
    if(sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(head);
}