#include <stdio.h>
#include <ctype.h>

#define MAX_SIZE            1024
#define TRUE                (1==1)
#define FALSE               (!TRUE)

int expand(char input[], char output[]);
int valid_range(char, char);

int main(void)
{
    int c, i;

    char input[MAX_SIZE];
    char output[MAX_SIZE];

    i = 0;
    while((c = getchar()) != EOF)
        input[i++] = c;

    input[i] = '\0';
    
    expand(input, output);

    printf("%s%s", input, output);

    return 0;
}

int expand(char s1[], char s2[])
{
    int i, j, je;

    i = j = je = 0;

    while((i < MAX_SIZE && j < MAX_SIZE) && s1[i] != '\0') {
        if(i > 0 && s1[i + 1] != '\0' && !je && s1[i] == '-' && valid_range(s1[i - 1], s1[i + 1])) {
            char tmp = s1[i - 1] + 1;
            while(tmp <= s1[i+1] && j < MAX_SIZE-1)
                s2[j++] = tmp++;
            i++;
            je = 1;
        }
        else
            s2[j++] = s1[i], je = 0;

        i++;
    }

    s2[j] = '\0';

    return 0;
}

int valid_range(char a, char b)
{
    if(a > b)
        return FALSE;
    if(isalpha(a) && isalpha(b)) {
        if(islower(a) && islower(b))
            return TRUE;
        else if(isupper(a) && isupper(b))
            return TRUE;
        else
            return FALSE;
    }
    else if(isdigit(a) && isdigit(b))
        return TRUE;

    return FALSE;
}