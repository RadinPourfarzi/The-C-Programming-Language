#include "token.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Tokenizer *init_tokenizer(const char *s)
{   
    Tokenizer *t;

    t = (Tokenizer *)malloc(sizeof(Tokenizer));

    if(t == NULL)
        return NULL;
    
    t->input = s;
    t->position = 0;

    return t;
}

void free_tokenizer(Tokenizer *t)
{
    if(t != NULL) {
        free(t);
        t = NULL;
    }
}

Token next_token(Tokenizer *t)
{
    Token tmp;
    char current_char;
    char next_char;

    while(TZR_POS(t) != '\0' && isspace((unsigned char)TZR_POS(t)))
        t->position++;

    if(TZR_POS(t) == '\0') {
        tmp.type = TOKEN_END;
        return tmp;
    }
    
    current_char = TZR_POS(t);
    next_char = t->input[t->position + 1];
    
    /*  Turning string input to double. */
    if(isdigit((unsigned char)current_char) || (current_char == '.' && isdigit((unsigned char)next_char))) {
        char *start_ptr;
        char *end_ptr;
        double token_value;

        start_ptr = &TZR_POS(t);

        token_value = strtod(start_ptr, &end_ptr);
        
        t->position += (end_ptr - start_ptr);

        tmp.num_value = token_value;
        tmp.type = TOKEN_NUMBER;
        return tmp;
    }

    if(isalpha((unsigned char)TZR_POS(t)) || TZR_POS(t) == '_') {
        int length;

        length = 0;
        while(isalnum((unsigned char)TZR_POS(t)) || TZR_POS(t) == '_') {
            if(length < MAX_TOKEN_NAME - 1)
                tmp.name[length++] = TZR_POS(t);

            t->position++;
        }
        tmp.name[length] = '\0';
        
        tmp.type = TOKEN_VARIABLE;

        return tmp;
    }

    /*  Checking each non-numeric token. */
    switch(TZR_POS(t)) {
        case '+':
            tmp.type = TOKEN_PLUS;
            t->position++;
            return tmp;
        case '-':
            tmp.type = TOKEN_MINUS;
            t->position++;
            return tmp;
        case '*':
            tmp.type = TOKEN_MULTIPLY;
            t->position++;
            return tmp;
        case '/':
            tmp.type = TOKEN_DIVIDE;
            t->position++;
            return tmp;
        case '=':
            tmp.type = TOKEN_ASSIGN;
            t->position++;
            return tmp;
        case '%':
            tmp.type = TOKEN_MODULO;
            t->position++;
            return tmp;
        case '(':
            tmp.type = TOKEN_LEFT_PAREN;
            t->position++;
            return tmp;
        case ')':
            tmp.type = TOKEN_RIGHT_PAREN;
            t->position++;
            return tmp;
        default:
            tmp.type = TOKEN_INVALID;
            return tmp;
    }

    tmp.type = TOKEN_INVALID;
    return tmp;
}