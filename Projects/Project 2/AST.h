#ifndef AST_H
#define AST_H

#include "token.h"

typedef struct abstract_syntax_tree_Node {
    Token token;
    struct abstract_syntax_tree_Node *left;
    struct abstract_syntax_tree_Node *right;
} AST_Node;

AST_Node *create_node(Token type, AST_Node *left, AST_Node *right);
void free_ast(AST_Node *node);

#endif