#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define MIN_SIZE        32

typedef struct file_buffer_data {
    char *buffer;
    unsigned int mem_cap;
    unsigned int size;
}   FileBuffer;

int get_line(int fd, FileBuffer *file_reader);
FileBuffer *start_buffer(int *error_status);
void free_buffer(FileBuffer *file_reader);

#endif