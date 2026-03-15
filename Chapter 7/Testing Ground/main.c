#include <stdio.h>
#include <stdlib.h>

int main()
{
    int status = system(".\\pipe.exe");
    printf("status = %d\n", status);
    return 0;
}
