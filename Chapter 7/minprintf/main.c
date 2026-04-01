//Unfinished

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *fmt, ...);
int descriptor_parser(char *input, int *precision, int *width, int *left_adj, char *type, int *width_given, int *precision_given);

int main(void)
{
    minprintf("Hello, %d\n", 19);
    return 0;
}

void minprintf(char *fmt, ...)
{
    va_list ap;     /* points to each unnamed arg in turn */
    char *p, *sval, type;
    int ival, precision, width, left_adj, width_given, precision_given;
    double dval;

    va_start(ap, fmt);   /* make ap point to first unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);   /* clean up when done */
}

/*
int descriptor_parser(char *input, int *precision, int *width, int *left_adj, char *type, int *width_given, int *precision_given)
{
    *precision = *width = *left_adj = 0;
    *precision_given = *width_given = 0;
    *type = '\0';

    if(*++input == '\0')
        return -1;       //return to signify end of string
    switch(*input) {
        case 'd':
            *type = 'd';
            return 1;   //return to signify no formating specified
        case 'f':
            *type = 'f';
            return 1;   //return to signify no formating specified  
        case 's':
            *type = 's';
            return 1;   //return to signify no formating specified
        case 'c':
            *type = 'c';
            return 1;   //return to signify no formating specified
        default:
            break;
    }

    if(*input == '-'){
        *left_adj = 1;
        input++;
    }
    while(isdigit(*input)) {
        *width_given = 1;
        *width = *width * 10 + (int)(*input++ - '0');
    }
    if(*input == '.') {
        input++;
        *precision_given = 1;
        if(!isdigit(*input)) {
            *precision_given = 0;
            return 0;    //return to signify error (no specified precision)
        }
        while(isdigit(*input)) {
            *precision = *precision * 10 + (int)(*input++ - '0');
        }
    }
    if(!isalpha(*input)) {
        if(*precision_given)
            return 0;   //return to signify error
        return 5;       //return to signify no arguments (didn't end in a character; therefore assume no formating was intended)
    }
    if(*input == 'c' && *precision_given)
        return 0;       //return to signify error (character does not format with precision)
    switch(*input)
    {
        case 'd':
            *type = 'd';
            break;
        case 'f':
            *type = 'f';
            break;  
        case 's':
            *type = 's';
            break;
        case 'c':
            *type = 'c';
            break;
        default:
            return 0;   //return to signify error (not supported type)
            break;
    }
    return 101;     //return to signify argument parsed correctly (something was found between '%' and a type specifier)
}
*/