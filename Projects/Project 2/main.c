/*  ##################################################
    ###      AST-Based Expression Interpreter      ###
    ##################################################  */

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "parser.h"
#include "AST.h"
#include "evaluate.h"

int main(int argc, char *argv[])
{
    Tokenizer *tokenizer;
    Parser *parser;
    AST_Node *head;
    double *result;
    int error;

    printf("%s\n", argv[1]);
    tokenizer = init_tokenizer(argv[1]);
    parser = init_parser(tokenizer);

    head = parse(parser);

    result = (double *)malloc(sizeof(double));

    error = evaluate(head, result);

    printf("%f\n%d\n", *result, error);

    return 0;
}