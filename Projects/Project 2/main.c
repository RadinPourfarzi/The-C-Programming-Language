/*  ##################################################
    ###      AST-Based Expression Interpreter      ###
    ##################################################  */

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "parser.h"
#include "AST.h"

int main(int argc, char *argv[])
{
    Tokenizer *tokenizer;
    Parser *parser;
    AST_Node *head;
    
    tokenizer = init_parser(argv[1]);
    parser = init_parser(tokenizer);

    head = parse(parser);

    return 0;
}