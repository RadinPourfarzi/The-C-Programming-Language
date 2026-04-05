#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f1p, *f2p;
    int c, s, lc_start, line;
    if((f1p = fopen(".\\f1.txt", "r")) == NULL) {
        fprintf(stderr, "%s cannot open f1.txt\n", argv[0]);
        exit(1);
    }
    if((f2p = fopen(".\\f2.txt", "r")) == NULL) {
        fprintf(stderr, "%s cannot open f2.txt\n", argv[0]);
        exit(1);
    }

    line = 1;
    lc_start = 0;
    while(1==1) {
        c = fgetc(f1p);
        s = fgetc(f2p);
        lc_start++;
        if(c == s) {
            if(c == EOF)
                break;
            if(c == '\n') {
                line++;
                lc_start = 0;
            }
            continue;
        }
        printf("line: %d\n", line);
        if(c == EOF) {
            printf("file1: EOF\n");
            break;
        }
        if(s == EOF) {
            printf("file2: EOF\n");
            break;
        }
        fseek(f1p, -lc_start, SEEK_CUR);
        fseek(f2p, -lc_start, SEEK_CUR);
        char buffer[1024];
        fgets(buffer, 1024, f1p);
        printf("file1: %s\n", buffer);
        fgets(buffer, 1024, f2p);
        printf("file2: %s\n", buffer);
        break;
    }
    
    fclose(f1p);
    fclose(f2p);
    return 0;
}