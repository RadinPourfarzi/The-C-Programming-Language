#ifndef SYMTAB_H
#define SYMTAB_H

#include "AST.h"
#include "token.h"

#define HASHSIZE        101

typedef unsigned int hash_value;

typedef struct symbol_list_node {
    struct symbol_list_node *next;
    Token token;
} sym_node;

sym_node *install(Token *t);
sym_node *lookup(const char *s);

#endif