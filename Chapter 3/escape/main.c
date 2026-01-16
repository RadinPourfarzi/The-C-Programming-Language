#include <stdio.h>

void escape(char input[], char output[]);
void unescape(char input[], char output[]);

int main(void)
{
    char input[256], output[256];
    int i, c;

    i = 0;

    while((c = getchar()) != EOF && i < 256)
        input[i++] = c;
    input[i] = '\0';

    escape(input, output);

    printf("%s\n", output);

    unescape(output, input);

    printf("%s\n", input);

    return 0;
}

void unescape(char s[], char t[])
{
    int i, j;

    i = j = 0;

    while(s[i] != '\0') {
        switch(s[i]) {
            case '\\':
                if(s[i+1] == 'n') {
                    t[j++] = '\n';
                    i += 2;
                }
                else if(s[i+1] == 't') {
                    t[j++] = '\t';
                    i += 2;
                }
                else {
                    t[j++] = s[i++];
                }
                break;
            default:
                t[j++] = s[i++];
                break;
        }
    }

    t[j] = '\0';

    return;
}

void escape(char s[], char t[])
{
    int i, j;

    i = j = 0;

    while(s[i] != '\0') {
        switch(s[i]) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                i++;
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                i++;
                break;
            default:
                t[j++] = s[i++];
        }
    }

    t[j] = '\0';

    return;
}