#ifndef TOKEN_H
#define TOKEN_H

#define TZR_POS(t)              ((t)->input[(t)->position])

typedef enum {
    TOKEN_NUMBER,
    TOKEN_VARIABLE,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_MODULO,
    TOKEN_ASSIGN,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_END,
    TOKEN_INVALID
} Token_Type;

typedef struct token_value_identifier {
    Token_Type type;
    double num_value;
} Token;

typedef struct tokenizer_metadata {
    const char *input;
    unsigned int position;
} Tokenizer;

Token next_token(Tokenizer *t);
Tokenizer *init_tokenizer(const char *s);

#endif