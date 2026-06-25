#include "AST.h"

#include <stdlib.h>

AST_Node *create_node(Token token, AST_Node *left, AST_Node *right)
{
    AST_Node *head;

    if((head = (AST_Node *)malloc(sizeof(AST_Node))) == NULL)
        return NULL;
    
    head->left = left;
    head->right = right;
    head->token = token;

    return head;
}   

void free_ast(AST_Node *node)
{
    if(node == NULL)
        return;

    free_ast(node->left);
    free_ast(node->right);

    free(node);
}