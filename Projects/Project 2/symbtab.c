#include "symtab.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static struct symbol_list_node *hashtable[HASHSIZE];

hash_value hash(const char *s)
{
    hash_value hashval;

    for(hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

sym_node *lookup(const char *s)
{
    sym_node *sn;
    for(sn = hashtable[hash(s)]; sn != NULL; sn = sn->next)
        if(strcmp(sn->token.name, s) == 0)
            return sn;
    return NULL;
}

sym_node *install(Token *t)
{
    sym_node *sn;
    hash_value hashval;

    if(t == NULL) {
        fprintf(stderr, "[Runtime Error]:symtab: Passed variable is NULL!");
        return NULL;
    }
    if((sn = lookup(t->name)) == NULL) {
        if((sn = (sym_node *)malloc(sizeof(sym_node))) == NULL) {
            fprintf(stderr, "[Runtime Error]: Error allocating sym_node!\n");
            return NULL;
        }
        if(!copy_token(&sn->token, t)) {
            free(sn);
            return NULL;
        }
        hashval = hash(sn->token.name);
        sn->next = hashtable[hashval];
        hashtable[hashval] = sn;
    }
    else {
        if(!copy_token(&sn->token, t)) {
            free(sn);
            return NULL;
        }
    }
    
    return sn;
}

void free_pocket(sym_node *sn)
{
    if(sn == NULL)
        return;
    free_pocket(sn->next);
    free(sn);
}