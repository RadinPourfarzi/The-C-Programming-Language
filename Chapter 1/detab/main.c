#include <stdio.h>

#define TAB_STOP        8
#define MAX_LINE        1025

int main(void)
{
    int c;
    int nc;

    nc = 0;

    while((c = getchar()) != EOF) {
        if(c == '\t') {
            int spaces = TAB_STOP - (nc % TAB_STOP);
            while(spaces != 0) {
                putchar(' ');
                --spaces;
                ++nc;
            }
        }
        else {
            putchar(c);
            ++nc;
            if(c == '\n') {
                nc = 0;
            }
        }
    }

    return 0;
}