#include <stdio.h>
#include <ctype.h>
#include <string.h>

void outUpper();
void outLower();

int main(int argc, char *argv[])
{
    int c;
    if(strstr(argv[0], "upper.exe"))
        outUpper();
    else if(strstr(argv[0], "lower.exe"))
        outLower();
    else
        while((c = getchar()) != EOF)
                putchar(c);
    return 0;
}

void outUpper()
{
    int c;
    while((c = getchar()) != EOF)
        putchar(toupper(c));
    
}

void outLower()
{
    int c;
    while((c = getchar()) != EOF)
        putchar(tolower(c));
}