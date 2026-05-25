#include <stdio.h>
#include <stdlib.h>

void *calloc(unsigned int n, unsigned int size);

int main()
{
    int *arr = calloc(10, sizeof(int));
    for(int i = 0; i < 10; i++)
        printf("%d\n", arr[i]);
    return 0;
}

void *calloc(unsigned int n, unsigned int size)
{
    void *p;
    register unsigned int n_size = n * size;
    if((p = malloc(n_size)) == NULL)
        return NULL;
    register unsigned char *ptr = (unsigned char*)p;
    while(n_size-- > 0) {
        *ptr++ = 0;
    }
    return p;
}