#include "search.h"

int strcontains(const char *haystack, const char *needle)
{
    if(*needle == '\0')
        return 0;

    for(; *haystack != '\0'; haystack++) {
        if(*haystack == *needle) {
            const char *h, *n;
            h = haystack;
            n = needle;

            while(*h != '\0' && *n != '\0' && *h == *n) {
                h++;
                n++;
            }
        
            if(*n == '\0')
                return (1==1);
        }
    }
    return !(1==1);
}