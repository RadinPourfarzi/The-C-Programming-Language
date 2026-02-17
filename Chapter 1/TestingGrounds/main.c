#include <stdio.h>

#define MAX     10000

int main()
{
    int nc, nl, c;
    nc = nl = 0;

    while((c = getchar()) != EOF) {
        if (c == '\n')
            ++nl;
        ++nc;
    }
    
    printf("Character count %d\nLine count %d\n", nc, nl);

    return 0;
}