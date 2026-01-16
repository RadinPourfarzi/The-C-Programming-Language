#include <stdio.h>

#define IN      1
#define OUT     0

power(base, n)
int base, n;
{
    return base * n;
}

int main()
{
    signed char c;
    int nl, nw, nc, wl, state;
    int wordLength[9];
    int charFreq[26];

    state = OUT;
    nl = nw = nc = wl = 0;

    for(int i = 0; i < 9; i++) {
        wordLength[i] = 0;
        charFreq[i] = 0;
    }
    for(int i = 9; i < 26; i++) {
        charFreq[i] = 0;
    }

    while((c = getchar()) != EOF) {
        ++nc;
        if(c == '\n') {
            ++nl;
        }
        if(c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if(wl >= 1) {
                ++wordLength[wl];
            }
            wl = 0;
        }
        else if(state == OUT) {
            state = IN;
            ++nw;
            ++charFreq[c - 'a'];
        }
        if(state == IN) {
            ++wl;
        }
    }

    printf("nl: %d, nw: %d, nc: %d\n", nl, nw, nc);

    for(int i = 0; i < 10; i++) {
        printf("%d|", i);
        for(int j = 0; j < wordLength[i]; j++) {
            printf("[\t]");
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i = 0; i < 26; i++) {
        printf("%c|", (i + 'a'));
        for(int j = 0; j < charFreq[i]; j++) {
            printf("[\t]");
        }
        printf("\n");
    }

    return 0;
}