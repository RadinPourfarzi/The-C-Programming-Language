#include <stdio.h>
#include <ctype.h>

int atoi(const char *);
int getline(char *s, int lim);

#define MAX_SIZE        1000

int main(int argc, char *argv[])
{
    char num1[MAX_SIZE];
    getline(num1, MAX_SIZE);
    printf("%d\n", atoi(num1));
    return 0;
}

int atoi(const char *s) 
{
    int n, sign;
    for( ; isspace((unsigned char)*s); s++)
        ;
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
        s++;
    for(n = 0; isdigit((unsigned char)*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

int getline(char *s, int lim)
{
    int c, i;
    for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++, s++)
        *s = c;
    if(c == '\n') {
        *s++ = c;
        i++;
    }
    *s = '\0';
    return i;
}