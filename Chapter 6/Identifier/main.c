#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE        1000

struct wnode {
    char *word;
    struct wnode *left;
    struct wnode *right;
};

struct pnode {
    char *prefix;
    struct wnode *words;
    struct pnode *left;
    struct pnode *right;
};

int getword(char *, int);
struct pnode *addptree(struct pnode *, char *, int);
struct wnode *addwtree(struct wnode *, char *);
struct pnode *palloc();
struct wnode *walloc();
int my_strncmp(const char *, const char *, int);
char *my_strndup(char *, int);
char *my_strncpy(char *, const char *, int );
int countwords(struct wnode *);
void printwtree(struct wnode *);
void printptree(struct pnode *);

int main(int argc, char **argv)
{
    int N = 6;
    if (argc > 1 && isdigit(argv[1][0]))
        N = atoi(argv[1]);
    
    struct pnode *head = NULL;
    char word[MAX_SIZE];
    while(getword(word, MAX_SIZE) != EOF)
        if(isalpha(word[0]))
            head = addptree(head, word, N);
    printptree(head);
    return 0;
}

int countwords(struct wnode *head)
{
    if (head == NULL)
        return 0;
    return 1 + countwords(head->left) + countwords(head->right);
}

void printwtree(struct wnode *head)
{
    if(head == NULL)
        return;
    printwtree(head->left);
    printf("\t%s\n", head->word);
    printwtree(head->right);
}

void printptree(struct pnode *head)
{
    if(head == NULL)
        return;
    printptree(head->left);
    if(countwords(head->words) > 1) {
        printf("Group (prefix: %s):\n", head->prefix);
        printwtree(head->words);
        printf("\n");
    }
    printptree(head->right);
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c == EOF)
        return EOF;
    *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break; 
        }
    *w = '\0';
    return word[0];
}

struct pnode *addptree(struct pnode *h, char *word, int size)
{
    int cond;
    
    if(h == NULL) {
        h = palloc();
        if(h == NULL)
            return NULL;
        h->prefix = my_strndup(word, size);
        h->left = h->right = NULL;
        h->words = NULL;
        h->words = addwtree(h->words, word);
    }
    else if((cond = my_strncmp(word, h->prefix, size)) == 0)
        h->words = addwtree(h->words, word);
    else if(cond < 0)
        h->left = addptree(h->left, word, size);
    else 
        h->right = addptree(h->right, word, size);
    return h;
}

struct wnode *addwtree(struct wnode *h, char *word)
{
    int cond;
    if(h == NULL) {
        h = walloc();
        if(h == NULL)
            return NULL;
        h->word = my_strndup(word, strlen(word));
        h->left = h->right = NULL;
    }        
    else if((cond = strcmp(word, h->word)) < 0)
        h->left = addwtree(h->left, word);
    else if(cond > 0)
        h->right = addwtree(h->right, word);
    return h;
}

struct pnode *palloc()
{
    return (struct pnode *)(malloc(sizeof(struct pnode)));
}

struct wnode *walloc()
{
    return (struct wnode *)(malloc(sizeof(struct wnode)));
}

int my_strncmp(const char *s, const char *t, int n)
{
    if(n <= 0)
        return 0;
    for( ; (*s != '\0') && (n > 0) && (*s == *t); s++, t++, n--)
        ;
    if(n == 0)
        return 0;
    return *(const unsigned char*)s - *(const unsigned char*)t;
}

char *my_strndup(char *s, int n)
{
    char *p;
    size_t len = strlen(s);
    if (len > (size_t)n)
        len = n;
    p = (char *) malloc(len + 1);
    if(p == NULL)
        return NULL;
    my_strncpy(p, s, len);
    return p;
}

char *my_strncpy(char *s, const char *t, int n)
{
    char *s_head = s;
    for( ; *t != '\0' && (s-s_head) < n; s++, t++)
        *s = *t;
    *s = '\0';
    return s_head;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}