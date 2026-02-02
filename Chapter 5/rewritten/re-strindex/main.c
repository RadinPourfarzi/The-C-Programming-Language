#include <stdio.h>

char *strindex(char *s, char *t);

#define MAX_SIZE        1000

char phrase[20] = "ould";

int main(int argc, char *argv[])
{
    char sentence[MAX_SIZE] = "This could, would, or should work?";
    char *pSentence = strindex(sentence, phrase);
    printf("%s\n", pSentence);
    return 0;
}

char *strindex(char *s, char *t)
{
    char *hs = s;
    char *ht = t;
    for( ; *hs != '\0'; hs++) {
        for(s = hs, t = ht; *t != '\0' && *s == *t; s++, t++)
            ;
        if(t > ht && *t == '\0')
            return hs;
    }
    return NULL;
}