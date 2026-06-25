#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "AST.h"

typedef struct parser_data {
    Tokenizer *tokenizer;
    Token current_token;
} Parser;

Parser *init_parser(Tokenizer *t);
void free_parser(Parser *p);

#endif