/*  ##################################################
    ###     Stack-Based Expression Interpreter     ###
    ##################################################  */

#include <stdio.h>

#include "token.h"

int main(int argc, char *argv[])
{
    Token toke;
    toke.type = advance(argv[1]);
    printf("%d\n", toke.type);
    toke.type = advance(argv[1]);
    printf("%d\n", toke.type);
    toke.type = advance(argv[1]);
    printf("%d\n", toke.type);
    toke.type = advance(argv[1]);
    printf("%d\n", toke.type);
    return 0;
}