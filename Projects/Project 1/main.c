/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE            100

int getword(char *word, int lim, FILE *stream);
int matchwords(const char *pattern, char *s);

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[MAX_SIZE];

    if((fp = fopen("File1.txt", "r")) == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return -1;
    }
    
    getword(buffer, MAX_SIZE, fp);
    /*printf("%s\n", buffer);*/

    printf("%d\n", matchwords("Verse", buffer));

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

int matchwords(const char *pattern, char *s)
{
    size_t len = (strlen(pattern) < strlen(s)) ? strlen(pattern) : strlen(s);
    printf("%d\n", len);
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