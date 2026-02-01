 #include <stdio.h>

 int main(int argc, char *argv[])
 {
    char str1[100] = "Hello, world!";
    char str2[20] = "world";
    printf("%d\n", strend(str1, str2));
    return 0;
 }

int strend(char *s, char *p)
{
    char *s_start, *p_start;
    s_start = s;
    p_start = p;

    while (*s) s++;
    while (*p) p++;
    for( ; s_start < s && p_start < p && *p == *s; s--, p--)
        ;
    if(p == p_start)
        return 1;
    return 0;
}