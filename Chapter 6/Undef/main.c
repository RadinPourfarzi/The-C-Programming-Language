#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist *install(char *, char *);
struct nlist *lookup(char *);
unsigned int hash(char *);

/* hash table entry */
struct nlist {
    struct nlist *next;  /* next entry in chain */
    char *name;          /* defined name */
    char *defn;          /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];  /* pointer table */

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

/* hash: form hash value for string s */
unsigned int hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;   /* found */

    return NULL;         /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {  /* already there */
        free((void *) np->defn);  /* free previous defn */
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}