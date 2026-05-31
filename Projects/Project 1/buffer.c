#include <stdlib.h>
#include "buffer.h"

FileBuffer file_reader = {NULL, 0, 0};

int start_buffer(void)
{   
    if(file_reader.buffer != NULL)
        return -1;
    if((file_reader.buffer = (char *)malloc(MIN_SIZE * sizeof(char))) == NULL)
        return -1;
    file_reader.buffer[0] = '\0';
    file_reader.mem_cap = MIN_SIZE;
    file_reader.size = 0;
    return 0;
}

void free_buffer(void)
{
    if(file_reader.buffer != NULL) {
        free(file_reader.buffer);
        file_reader.buffer = NULL;
    }
    file_reader.mem_cap = 0;
    file_reader.size = 0;
}

int get_line(int fd)
{
    file_reader.size = 0;
    char *new_buffer = NULL;
    unsigned int new_mem_cap;
    char c;
    unsigned int bytes_read;

    while((bytes_read = read(fd, &c, 1)) > 0) {
        if(file_reader.size + 1 > file_reader.mem_cap) {
            new_mem_cap = file_reader.mem_cap * 2;
            if((new_buffer = (char *)realloc(file_reader.buffer, new_mem_cap)) == NULL)
                return -1;
            file_reader.buffer = new_buffer;
            file_reader.mem_cap = new_mem_cap;
        }
        
        file_reader.buffer[file_reader.size] = c;
        file_reader.size++;

        if(c == '\n')
            break;
    }

    file_reader.buffer[file_reader.size] = '\0';

    if(bytes_read < 0)  return -1;
    if(bytes_read == 0 && file_reader.size == 0) return 0;
    return 1;
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