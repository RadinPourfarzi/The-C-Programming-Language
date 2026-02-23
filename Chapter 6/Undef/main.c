#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist *install(char *, char *);
struct nlist *lookup(char *);
unsigned int hash(char *);

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

int main(int argc, char **argv)
{
    return 0;
}

void undef(char *name)
{
    struct nlist *np, *lp;
    int index = hash(name);

    if(lookup(name) == NULL) {
        return;
    }

    for(np = hashtab[index], lp = NULL; np != NULL; lp = np, np = np->next) {
        if(strcmp(name, np->name) == 0) {
            if(lp == NULL)
                hashtab[index] = np->next;
            else
                lp->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
    }
}

unsigned int hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;

    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}