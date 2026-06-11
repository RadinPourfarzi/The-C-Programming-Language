/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "search.h"
#include "options.h"

int main(int argc, char *argv[])
{
    int fd, status, flags;

    check_condition(argc, argv);
    printf("%d, %d, %s\n", arg_manager.conditions, arg_manager.flags, arg_manager.pattern);
    read_flags();
    return 0;
    if(argc < 2)
        fd = 1;
    else {
        if((flags = check_options(argv[1])) == ERROR_O) {
            perror("Non proper option!\n");
            return -1;
        }
        int i = (flags == -1) ? 1 : 2;
        for( ; i < argc; i++) {
            printf("%s\n", argv[i]);

            start_buffer();

            /*if(!check_file(argv[i])) {
                perror("Improper File!\n");
                return -1;
            }*/
            if((fd = open(argv[i], O_RDONLY)) < 0) {
                perror("Error opening file");
                return -1;
            }
            while((status = get_line(fd)) > 0) {
            if(strcontains(file_reader.buffer, "Verse"))
                printf("[Len: %zu | Cap: %zu] %s", file_reader.size, file_reader.mem_cap, file_reader.buffer);
            }

            close(fd);
            free_buffer();
        }
    }

    return 0;
}