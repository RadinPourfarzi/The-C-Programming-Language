#include "token.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

Token_Type advance(char *input)
{
    static int offset = 0;
    printf("input: %c\n", *(input + offset));
    offset += sizeof(char);
    return identify_input(input + offset);
}

Token_Type identify_input(char *s)
{
    while(isspace((int)*s))
        s++;
    if(isdigit((int)*s))
        return NUMBER;
    if(isalpha((int)*s))
        return VARIABLE;
    switch(*s) {
        case '+':
        case '-':
        case '/':
        case '*':
            return OPERATOR;
        case '=':
            return ASSIGN;
        case '(':
            return LEFT_PAR;
        case ')':
            return RIGHT_PAR;
        default:
            return -1;
    }
    return -1;
}