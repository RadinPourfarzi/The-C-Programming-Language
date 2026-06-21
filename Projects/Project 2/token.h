#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_END,
    TOKEN_INVALID
} Token_Type;

typedef struct token_value_identifier {
    Token_Type type;
    double num_value;
    char var_name[32];
} Token;

#endif