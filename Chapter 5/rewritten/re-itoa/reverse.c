#include <stdio.h>

void reverse(char *s)
{
    char tmp;
    char *t = s;
    while(*t != '\0')
        t++;
    t--;
    for( ; s < t; s++, t--) {
        tmp = *s;
        *s = *t;
        *t = tmp;
    }
}