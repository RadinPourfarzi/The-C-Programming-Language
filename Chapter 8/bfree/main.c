#include <stdio.h>
#include <stdlib.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

int main()
{
    char buf[1000];
    unsigned int n = 10000/sizeof(Header);
    printf("%d, %d, %d\n", sizeof(buf), sizeof(Header), n);
    return 0;
}

void bfree(void *p, unsigned int n)
{
    Header *head_p = (Header *)p;
    if((head_p->s.size = n/sizeof(Header)) < 2)
        return;
    free(++head_p);
}