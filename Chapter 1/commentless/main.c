#include <stdio.h>

#define NORMAL      0
#define IN_COMMENT  1
#define IN_STRING   2
#define IN_CHAR     3

#define TRUE        1==1
#define FALSE       !TRUE

int main(void)
{
    int c, state, escaped;
    char prev;

    prev = 0;

    state = NORMAL;
    escaped = FALSE;

    while((c = getchar()) != EOF) {
        if(state == NORMAL) {
            if(c == '*' && prev == '/') {
                state = IN_COMMENT;
                prev = 0;
            }
            else {
                if(c == '"') {
                    state = IN_STRING;
                    escaped = FALSE;
                }
                else if(c == '\'') {
                    state = IN_CHAR;
                    escaped = FALSE;
                }

                if(prev == '/')
                    putchar('/');

                if(c != '/')
                    putchar(c);
            }

            prev = c;
        }
        else if(state == IN_COMMENT) {
            if(prev == '*' && c == '/') {
                state = NORMAL;
                prev = 0;
            }
            else {
                prev = c;
            }
        }
        else if(state == IN_STRING) {
            if(c == '"' && !escaped) {
                state = NORMAL;
            }
            escaped = (c == '\\' && !escaped);
            putchar(c);
        }
        else {
            if(c == '\'' && !escaped) {
                state = NORMAL;
            }
            escaped = (c == '\\' && !escaped);
            putchar(c);
        }
    }

    if (state == NORMAL && prev == '/')
        putchar('/');

    return 0;
}