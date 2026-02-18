#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE        1000

struct wnode {
    char *word;              // full identifier
    struct wnode *left;      // left child (alphabetically smaller)
    struct wnode *right;     // right child (alphabetically larger)
};

struct pnode {
    char *prefix;            // first N characters of a word
    struct wnode *words;     // BST of full identifiers sharing this prefix
    struct pnode *left;      // left child (alphabetically smaller)
    struct pnode *right;     // right child (alphabetically larger)
};

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

#define NKEYS (int)(sizeof(keywords)/sizeof(keywords[0]))

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
int iskeyword(char *word);

int main(int argc, char **argv)
{
    int N = 6;
    if (argc > 1 && isdigit(argv[1][0]))
        N = atoi(argv[1]);
    
    struct pnode *head = NULL;
    char word[MAX_SIZE];
    while(getword(word, MAX_SIZE) != EOF)
        if(isalpha(word[0]) && !iskeyword(word))
            head = addptree(head, word, N);
    printptree(head);
    return 0;
}

/*
   Returns total number of words in a word BST.
   Used to determine whether a prefix group has >1 identifiers.
*/

int countwords(struct wnode *head)
{
    if (head == NULL)
        return 0;
    return 1 + countwords(head->left) + countwords(head->right);
}

/*
   Prints full identifiers alphabetically.
*/

void printwtree(struct wnode *head)
{
    if(head == NULL)
        return;
    printwtree(head->left);
    printf("\t%s\n", head->word);
    printwtree(head->right);
}

/*
   Traverses prefix BST alphabetically.
   Only prints groups that contain more than one word.
*/

void printptree(struct pnode *head)
{
    if(head == NULL)
        return;
    printptree(head->left);
    if(countwords(head->words) > 1) {   // Only print groups with more than one identifier
        printf("Group (prefix: %s):\n", head->prefix);
        printwtree(head->words);
        printf("\n");
    }
    printptree(head->right);
}

/*
   Reads next word from input.
   Uses getch/ungetch for one-character pushback.

   Returns:
       - EOF on end of file
       - first character of word otherwise
*/

int getword(char *word, int lim)
{
    int c, getch(void), isComStrChar(int);
    void ungetch(int);
    char *w = word;
    while(1==1) {
        if ((c = getch()) == EOF)
            return EOF;
        int cond = isComStrChar(c);
        if(cond)
            continue;
        if(!isspace(c)) // Skip whitespace
            break;
    }
    *w++ = c;
    if (!isalpha(c)) { // If not alphabetic, return single-character token
        *w = '\0';
        return c;
    }
   while (--lim > 0) {
        if ((c = getch()) == EOF)
            break;
        if (isComStrChar(c) || !isalnum(c)) {
            ungetch(c);
            break;
        }
        *w++ = c;
    }
    *w = '\0';
    return word[0];
}

/*
    Checks if word is in list of known Keywords.
*/

int iskeyword(char *word)
{
    for (int i = 0; i < NKEYS; i++)
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    return 0;
}

/*
   Inserts word into prefix BST.
   If prefix already exists, insert word into its word BST.
*/

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

/*
   Standard BST insertion using strcmp.
   Keeps words alphabetically ordered.
*/

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

/* Memory allocation helpers */
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

#define NORMAL      0
#define IN_COMMENT  1
#define IN_STRING   2
#define IN_CHAR     3

#define TRUE        (1==1)
#define FALSE       (!TRUE)

int isComStrChar(int c)
{
    static int prev = 0;
    static int state = NORMAL;
    static int escaped = FALSE;

    if(state == NORMAL) {
        if(c == '*' && prev == '/') {
            state = IN_COMMENT;
            prev = 0;
        }
        else {
            if(c == '"') {
                state = IN_STRING;
                escaped = FALSE;
            }
            else if(c == '\'') {
                state = IN_CHAR;
                escaped = FALSE;
            }
        }
        prev = c;
        return FALSE;
    }
    else if(state == IN_COMMENT) {
        if (prev == '*' && c == '/')
            state = NORMAL;
        prev = c;
        return TRUE;
    }
    else if(state == IN_STRING) {
        if (c == '"' && !escaped)
            state = NORMAL;
        escaped = (c == '\\' && !escaped);
        return TRUE;
    }
    else if(state == IN_CHAR) {
        if (c == '\'' && !escaped)
            state = NORMAL;
        escaped = (c == '\\' && !escaped);
        return TRUE;
    }

    prev = c;
    return FALSE;
}