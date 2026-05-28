/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE            1000

int getword(char *word, int lim, FILE *stream);
int matchwords_len(const char *pattern, size_t len, char *s);
int *find_repeat_words(const char *pattern, char *s);
int linecount(char *s);

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[MAX_SIZE];
    int *l_list, i;

    if((fp = fopen("File1.txt", "r")) == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return -1;
    }
    
    getword(buffer, MAX_SIZE, fp);
    printf("%s\n\n", buffer);

    l_list = find_repeat_words("Verse", buffer);
    for(i = 0; i < linecount(buffer); i++)
        printf("line: %d\n", l_list[i]);

    return 0;
}

int getword(char *word, int lim, FILE *stream)
{
    int c = 0;
    char *w = word;

    for(c = getc(stream); --lim > 0; c = getc(stream)) {
        /*printf("%d: %d\n", lim, c);*/
        if(c == EOF) {
            ungetc(*w, stream);
            break;
        }
        *w++ = c;
    }
    *w = '\0';
    return word[0];
}

int linecount(char *s)
{
    int i = 0;
    while(*s-- != '\0')
        if(*s == '\n')
            i++;
    return i;
}

int *find_repeat_words(const char *pattern, char *s)
{
    size_t len = strlen(pattern);
    int *l_list = (int*)malloc(linecount(s)), *sl_list;
    unsigned int line = 0;
    
    sl_list = l_list;

    if(len > strlen(s))
        return NULL;
    else if(len == strlen(s))
        return (strcmp(pattern, s) == 0) ? NULL : NULL;
    printf("1\t");
    while(*s != '\0') {
        line++;
        printf("2\t");
        if(matchwords_len(pattern, len, s)) {
            printf("5\t");
            *l_list++ = line;
        }
        s += len + 1;
    }   
    return sl_list;
}

int matchwords_len(const char *pattern, size_t len, char *s)
{
    printf("3\t");
    while(*s++ != '\0') {
        if(*s == pattern[0]) {
            for( ; (--len > 0 && *pattern == *s) && (*s != '\0'); pattern++, s++)
                ;
            printf("4\t");
            if(len == 0)
                return 1;
        }
    }
    return 0;
}

/*
int matchwords(const char *pattern, char *s)
{
    size_t len = strlen(pattern);

    if(len > strlen(s))
        return NULL;
    else if(len == strlen(s))
        return (strcmp(pattern, s) == 0) ? &s : NULL;
    while(*s++ != EOF) {
        if(*s == pattern[0]) {
            for( ; (--len > 0 && *pattern == *s) && (*s != EOF); pattern++, s++)
                ;
            if(len == 0)
                return 1;
        }
    }
    return 0;
}
*/