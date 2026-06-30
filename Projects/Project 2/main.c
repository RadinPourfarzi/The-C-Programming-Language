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

void free_all(FileBuffer *f, Tokenizer *t, Parser *p, AST_Node *h);
FileBuffer *start_buffer(void);

int main(int argc, char *argv[])
{
    Tokenizer *tokenizer;
    Parser *parser;
    AST_Node *head;
    FileBuffer *file_reader;

    double result;
    int error;

    file_reader = start_buffer();
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
            free_all(file_reader, tokenizer, parser, head);
            file_reader = start_buffer();
            continue;
        }
        if(!evaluate(head, &result)) {
            free_all(file_reader, tokenizer, parser, head);
            file_reader = start_buffer();
            continue;
        }
        printf("%f\n", result);

        free_all(file_reader, tokenizer, parser, head);

        file_reader = start_buffer();
    }

    return 0;
}

void free_all(FileBuffer *f, Tokenizer *t, Parser *p, AST_Node *h)
{
    free_buffer(f);
    free_tokenizer(t);
    free_parser(p);
    free_ast(h);
}

FileBuffer *start_buffer(void)
{
    FileBuffer *fr;
    int error;

    fr = init_buffer(&error);
    if(error == -1) {
        fprintf(stderr, "[Runtime Error]: Error starting Buffer!\n");
        return NULL;
    }

    return fr;
}