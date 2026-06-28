#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

#define advance(parser)        (parser->current_token = next_token(parser->tokenizer))

AST_Node *parse(Parser *p);
AST_Node *primary(Parser *p);
AST_Node *term(Parser *p);
AST_Node *expression(Parser *p);
AST_Node *assign(Parser *p);

Parser *init_parser(Tokenizer *t)
{
    Parser *p;

    if((p = (Parser *)malloc(sizeof(Parser))) == NULL)
        return NULL;

    p->tokenizer = t;
    advance(p);

    return p;
}

void free_parser(Parser *p)
{
    if(p != NULL) {
        free(p);
        p = NULL;
    }
}

AST_Node *parse(Parser *p)
{
    AST_Node *root;

    if((root = assign(p)) == NULL)
        return NULL;
    
    if(p->current_token.type != TOKEN_END) {
        free_ast(root);
        return NULL;
    }
    return root;
}

AST_Node *assign(Parser *p)
{
    AST_Node *left;
    AST_Node *right;
    Token current_t;

    if((left = expression(p)) == NULL)
        return NULL;

    if(p->current_token.type != TOKEN_ASSIGN) {
        return left;
    }
    
    if(left->token.type != TOKEN_VARIABLE)
        return NULL;
    
    current_t = p->current_token;

    advance(p);

    if((right = assign(p)) == NULL)
        return NULL;

    left = create_node(current_t, left, right);
    return left;
}

AST_Node *expression(Parser *p)
{
    AST_Node *left;
    AST_Node *right;

    if((left = term(p)) == NULL)
        return NULL;

    while(p->current_token.type == TOKEN_PLUS || p->current_token.type == TOKEN_MINUS) {
        Token current_t;
        current_t = p->current_token;

        advance(p);

        if((right = term(p)) == NULL)
            return NULL;

        left = create_node(current_t, left, right);
    }
    return left;
}

AST_Node *term(Parser *p)
{
    AST_Node *left;
    AST_Node *right;

    if((left = primary(p)) == NULL)
        return NULL;

    while(p->current_token.type == TOKEN_MULTIPLY || p->current_token.type == TOKEN_DIVIDE || p->current_token.type == TOKEN_MODULO) {
        Token current_t;
        current_t = p->current_token;

        advance(p);

        if((right = primary(p)) == NULL)
            return NULL;

        left = create_node(current_t, left, right);
    }
    return left;
}
/*
AST_Node *exponent(Parser *p)
{
    AST_Node *left;
    AST_Node *right;

    left = primary(p);

    return left;
} */

AST_Node *primary(Parser *p)
{
    AST_Node *node;

    node = NULL;

    if(p->current_token.type == TOKEN_NUMBER) {
        Token current_t;
        current_t = p->current_token;

        advance(p);

        node = create_node(current_t, NULL, NULL);
        return node;
    }

    if (p->current_token.type == TOKEN_LEFT_PAREN) {
        advance(p);

        if((node = assign(p)) == NULL)
            return NULL;

        if (p->current_token.type != TOKEN_RIGHT_PAREN) {
            free_ast(node);
            fprintf(stderr, "[Syntax Error]: Missing closing parenthesis - \'...)\'\nReceived token type %d\n", p->current_token.type);
            return NULL;
        }

        advance(p);
        return node;
    }

    return node;
}