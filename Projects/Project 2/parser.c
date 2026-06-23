#include "parser.h"

AST_Node *assign(Parser *p)
{
    AST_Node *left;

    left = expression(p);

    return left;
}

AST_Node *expression(Parser *p)
{
    AST_Node *left;

    left = term(p);

    return left;
}

AST_Node *term(Parser *p)
{
    AST_Node *left;

    left = exponent(p);

    return left;
}

AST_Node *exponent(Parser *p)
{
    AST_Node *left;

    left = primary(p);

    return left;
}

AST_Node *primary(Parser *p)
{
    AST_Node *node;

    return node;
}