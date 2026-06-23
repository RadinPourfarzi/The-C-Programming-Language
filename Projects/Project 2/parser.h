#ifndef PARSER_H
#define PARSER_H

#include "token.h"

typedef struct parser_data {
    Tokenizer *tokenizer;
    Token current_token;
} Parser;

typedef struct abstract_syntax_tree_Node {
    Token token;
    struct abstract_syntax_tree_Node *left;
    struct abstract_syntax_tree_Node *right;
} AST_Node;

#endif