#include <stdio.h>

#define OUT                 0
#define IN                  1
#define MAX_LINE_LENGTH     80

void putBuffer(char buffer[256], short int state);

int main(void)
{
    short int c, state, i;
    char buffer[256];
    int nc;

    state = OUT;
    nc = i = 0;

    while((c = getchar()) != EOF) {
        if(c == ' ' || c == '\t') {
            ++nc;
            buffer[i] = '\0';
            if(nc > MAX_LINE_LENGTH) {
                putchar('\n');
                putBuffer(buffer, state);
                putchar(' ');
                nc = 0;
            }
            else {
                putBuffer(buffer, state);
                putchar(c);
            }
            
            state = OUT;
            i = 0;
        }
        else if(c == '\n') {
            nc = 0;
            putchar(c);
            putBuffer(buffer, state);
            state = OUT;
            i = 0;
        }
        else {
            state = IN;
            buffer[i] = c;
            ++i;
            ++nc;
        }
    }
    return 0;
}

void putBuffer(char buffer[256], short int state)
{
    if(state == IN) {
        int i = 0;
        while(buffer[i] != '\0') {
            putchar(buffer[i]);
            ++i;
        }
    }
}