#include <stdio.h>
#include <ctype.h>

#define LINE_MAX        80

int main(int argc, char *argv[])
{
    int c, cc;
    cc = 0;
    while((c = getchar()) != EOF) {
        if(isprint(c)) {
            putchar(c);
            cc++;
        }
        else {
            printf("0x%x", c);
            if(c < 16)
                cc += 3;
            else
                cc += 4;
        }
        if(cc >= LINE_MAX) {
            putchar('\n');
            cc = 0;
        }
    }
    return 0;
}