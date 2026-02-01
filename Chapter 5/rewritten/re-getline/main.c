#include <stdio.h>

int getline(char *string, int limit);

int main(int argc, char *argv[])
{
    char s[1000];
    printf("%d\t%s\n", getline(s, 1000), s);
    return 0;
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