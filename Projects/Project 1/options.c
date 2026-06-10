#include "options.h"
#include <ctype.h>

static int flags = 0;

int check_options(char *arguments)
{
    char *s;
    
    s = arguments;

    if(*s++ != '-')
        return (flags = -1);
    while(*s != '\0') {
        switch(*s) {
            case 'i':
                flags |= IGNORE_CASE;
                break;
            case 'v':
                flags |= INVERT_MATCH;
                break;
            case 'n':
                flags |= LINE_NUMBERS;
                break;
            case 'c':
                flags |= COUNT_MATCHES;
                break;
            default:
                flags |= ERROR;
                return flags;
        }
        s++;
    }
    return flags;
}

int check_file(char *filename)
{
    char *s;

    s = filename;
    
    if(s == '\0')
        return 0;
    while(*filename++ != '\0') {
        if(*filename == '.')
            break;
        if(!isalnum((int)(*filename)))
            return 0;
    }
    return 1;
}