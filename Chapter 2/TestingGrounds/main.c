#include <stdio.h>
#include <float.h>
#include <limits.h>

#define TRUE        1==1
#define FALSE       !TRUE

typedef enum boolean {True = TRUE, False = FALSE} bool;

int main(void)
{
    bool isInside;
    isInside = False;
    if(isInside)
        printf("True");
    else
        printf("False");

    int x = 1;
    x = x ^ 2;
    printf("\n%d\n", x);

    return 0;
}