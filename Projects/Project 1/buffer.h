#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#ifndef BUFFER_H
#define BUFFER_H

#define MIN_SIZE        64

typedef struct {
    char *buffer;
    unsigned int mem_cap;
    unsigned int size;
}   FileBuffer;

extern FileBuffer file_reader;

int get_line(int fd);
int start_buffer(void);
void free_buffer(void);
int getword(char *word, int lim, FILE *stream);

#endif