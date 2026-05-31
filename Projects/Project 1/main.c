/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include "buffer.h"

int main(int argc, char *argv[])
{
    int fd, status;

    if((fd = open("File1.txt", O_RDONLY)) < 0) {
        perror("Error opening file");
        return -1;
    }

    start_buffer();
    
    while((status = get_line(fd)) > 0)
        printf("[Len: %zu | Cap: %zu] %s", file_reader.size, file_reader.mem_cap, file_reader.buffer);
    
    close(fd);
    free_buffer();

    return 0;
}