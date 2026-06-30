#include "AST.h"

#include <stdlib.h>
#include <stdio.h>

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

void print_ast(AST_Node *node, int depth)
{
    int i;

    if (node == NULL)
        return;

    for (i = 0; i < depth; i++)
        printf("  ");

    printf("%p: type=%d left=%p right=%p\n", (void *)node, node->token.type, (void *)node->left, (void *)node->right);

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}