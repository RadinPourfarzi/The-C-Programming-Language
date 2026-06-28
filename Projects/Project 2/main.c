/*  ##################################################
    ###      AST-Based Expression Interpreter      ###
    ##################################################  */

#include <stdio.h>
#include <stdlib.h>

#include "token.h"
#include "parser.h"
#include "AST.h"
#include "evaluate.h"
#include "buffer.h"

int main(int argc, char *argv[])
{
    Tokenizer *tokenizer;
    Parser *parser;
    AST_Node *head;
    FileBuffer *file_reader;

    double result;
    int error;

    file_reader = start_buffer(&error);
    if(error == -1) {
        fprintf(stderr, "[Runtime Error]: Error starting Buffer!\n");
        return 1;
    }
    while((error = get_line(0, file_reader)) == 1) {
        if((tokenizer = init_tokenizer(file_reader->buffer)) == NULL) {
            fprintf(stderr, "[Runtime Error]: Error initializing tokenizer!\n");
            return 1;
        }
        if((parser = init_parser(tokenizer)) == NULL) {
            fprintf(stderr, "[Runtime Error]: Error initializing parser!\n");
            return 1;
        }
        if((head = parse(parser)) == NULL) {
            fprintf(stderr, "[Parsing Error]\n");
            free_buffer(file_reader);
            free_tokenizer(tokenizer);
            free_parser(parser);
            free_ast(head);
            continue;
        }
        if(!evaluate(head, &result)) {
            fprintf(stderr, "[calculation error]\n");
            free_buffer(file_reader);
            free_tokenizer(tokenizer);
            free_parser(parser);
            free_ast(head);
            continue;
        }
        printf("%f\n", result);

        free_buffer(file_reader);
        free_tokenizer(tokenizer);
        free_parser(parser);
        free_ast(head);

        file_reader = start_buffer(&error);
        if(error == -1) {
            fprintf(stderr, "[Runtime Error]: Error starting Buffer!\n");
            return 1;
        }
    }

    return 0;
}