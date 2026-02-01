#include <stdio.h>

void strcat(char *, char *);

int main(int argc, char *argv[])
{
    char str1[100] = "Hello, ";
    char str2[20] = "World";
    strcat(str1, str2);
    printf("%s\n", str1);
    return 0;
}

void strcat(char *s, char *t)
{
    while(*s != '\0')
        s++;
    while((*s++ = *t++) != '\0')
        ;
}