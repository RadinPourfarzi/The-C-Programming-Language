#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    VARIABLE,
    NUMBER,
    ASSIGN,
    OPERATOR,
    LEFT_PAR,
    RIGHT_PAR
} Token_Type;

typedef struct token_value_identifier {
    Token_Type type;
    double num_value;
    char var_name[32];
} Token;

Token_Type identify_input(char *);
Token_Type advance(char *input);

#endif