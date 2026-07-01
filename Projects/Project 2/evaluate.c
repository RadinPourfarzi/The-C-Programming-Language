#include "evaluate.h"

#include <stdio.h>

#include "symtab.h"

int evaluate(AST_Node *root, double *result)
{
    double a, b;

    if(result == NULL) {
        fprintf(stderr, "[Evaluate Error]: result pointer is NULL!\n");
        return 0;
    }

    if(root == NULL) {
        fprintf(stderr, "[Evaluate Error]: root is NULL!\n");
        return 0;
    }

    if(root->token.type == TOKEN_END) {
        fprintf(stderr, "[Evaluate Error]: root is at end!\n");
        return 0;
    }
    
    if(root->token.type == TOKEN_ASSIGN) {
        sym_node *sn;

        if(root->left->token.type != TOKEN_VARIABLE) {
            fprintf(stderr, "[Assignment Error]: Nothing to assign to!\n");
            return 0;
        }
        if(!evaluate(root->right, result))
            return 0;

        root->left->token.num_value = *result;
        if((sn = install(&root->left->token)) == NULL) {
            fprintf(stderr, "[Runtime Error]:evaluate: Error installing token!\n");
            return 0;
        }
        return 1;
    }
    if(root->left != NULL && root->right == NULL) {
        if(root->token.type == TOKEN_MINUS) {
            if(!evaluate(root->left, result))
                return 0;
            *result *= -1;
            return 1;
        }
        fprintf(stderr, "[Evaluate Error]: node has one tail!\n");
        return 0;
    }
    else if(root->right == NULL && root->left == NULL) {
        if(root->token.type == TOKEN_NUMBER) {
            *result = root->token.num_value;
            return 1;
        }
        if(root->token.type == TOKEN_VARIABLE) {
            sym_node *sn;
            printf("Variable name: %s\n", root->token.name);
            if((sn = lookup(root->token.name)) == NULL) {
                fprintf(stderr, "[Runtime Error]:evaluate: Failure looking up!\n");
                return 0;
            }
            *result = sn->token.num_value;
            return 1;
        }
        fprintf(stderr, "[Evaluate Error]: node has no tails!\n");
        return 0;
    }
    else if(root->right != NULL && root->left != NULL) {
        if(!evaluate(root->left, result))
            return 0;
        a = *result;
        if(!evaluate(root->right, result))
            return 0;
        b = *result;
    }

    switch(root->token.type) {
        case TOKEN_PLUS:
            *result = a + b;
            return 1;
        case TOKEN_MINUS:
            *result = a - b;
            return 1;
        case TOKEN_MULTIPLY:
            *result = a * b;
            return 1;
        case TOKEN_DIVIDE: {
            if(b == 0) {
                fprintf(stderr, "[Evaluate Error]: Divide by Zero!\n");
                return 0;
            }
            *result = a / b;
            return 1;
        }
        case TOKEN_MODULO: {
            if(b == 0) {
                fprintf(stderr, "[Evaluate Error]: Divide by Zero!\n");
                return 0;
            }
            if(a == (int)a && b == (int)b) {
                *result = (int)a % (int)b;
                return 1;
            }
            fprintf(stderr, "[Evaluate Error]: Can only use modulo on integers!\n");
            return 0;
        }
        default:
            fprintf(stderr, "[Evaluate Error]: Something went wrong!\n");
            return 0;
    }
    
    return 0;
}