#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int getint(int *);

int main(int argc, char *argv[])
{
    int x = 0;
    while(getint(&x))
        ;
    printf("%d\n", x);
    return 0;
}


int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);                /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int sign_c = c;
        c = getch();
        if(!isdigit(c)) {
            ungetch(c);
            ungetch(sign_c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * (*pn) + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
