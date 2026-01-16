#include <stdio.h>

#define TAB_STOP        8
#define MAX_LINE        1025

int main(void)
{
    short int c;
    int nc, ns;

    nc = ns = 0;

    while((c = getchar()) != EOF) {
        if(c == ' ') {
            ++ns;
            ++nc;
        }
        else {
            while(ns > 0) {
                unsigned short int tt = TAB_STOP - (nc - ns) % TAB_STOP;

                if(ns >= tt && tt > 0) {
                    putchar('\t');
                    ns = ns - tt;
                }
                else {
                    putchar(' ');
                    --ns;
                }
            }
            putchar(c);
            ++nc;
            if(c == '\n') {
                nc = 0;
            }
        }
    }

    while(ns > 0) {
        --ns;
        putchar(' ');
    }

    return 0;
}