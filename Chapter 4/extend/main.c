#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE         1000

int getline(char line[], int max);
double atof(char line[]);

int main(void)
{
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0)
        printf("%f\n", atof(line));
    
    return 0;
}

int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

double atof(char s[])
{
    double val, power;
    int i, sign, esign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit((unsigned char)s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    printf("%f\n", val);
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit((unsigned char)s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    if(s[i] == 'e')
        i++;
    else
        return sign * val / power;
    val = val / power;
    esign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for(power = 0.0; isdigit((unsigned char)s[i]); i++)
        power = 10.0 * power + (s[i] - '0');
    printf("%f\n", power);
    while (power-- > 0)
        val = (esign == 1) ? val * 10.0 : val / 10.0;
    return val;
}