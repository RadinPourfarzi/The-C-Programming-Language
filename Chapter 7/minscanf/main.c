#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minscanf(char *fmt, ...);
int getword(char *word, int lim);

int main()
{
    int i;
    char str[1000];
    minscanf("Please enter digit: %s", &str);
    printf("%s", str);
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *ch, *str;
    int *ival, c;
    double *dbval;

    va_start(ap, fmt);   /* make ap point to first unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int*);
            *ival = 0;
            c = 0;
            while(isspace(c=getchar()))
                ;
            while(c != EOF  && isdigit(c)) {
                *ival = *ival * 10 + (c - '0');
                c = getchar();
            }
            break;
        case 'f':
            dbval = va_arg(ap, double*);
            *dbval = 0;
            c = 0;
            for(c = getchar(); c != EOF && c != ' ' && c != '\n'; )
                *dbval = *dbval * 10.0 + (c - '0');
            break;
        case 's':
            str = va_arg(ap, char*);
            getword(str, 1000);
            break;
        case 'c':
            ch = va_arg(ap, char*);
            *ch = getchar();
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);   /* clean up when done */
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);

    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    for ( ; --lim > 0; w++)
        if ((*w = getch()) != EOF && isspace(*w)) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}