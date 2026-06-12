/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "buffer.h"
#include "search.h"
#include "options.h"

int main(int argc, char *argv[])
{
    int fd, status, i;
    unsigned int file_count, line_count, line_num;

    check_condition(argc, argv);

    if(!(arg_manager.conditions & GIVEN_PATTERN))
        getword((char *)arg_manager.pattern, 1024, stdin);
    if(!(arg_manager.conditions & GIVEN_FILES))
        fd = 1;

    i = 1;
    if((arg_manager.conditions & GIVEN_PATTERN) == GIVEN_PATTERN)
        i++;
    if((arg_manager.conditions & GIVEN_OPTION) == GIVEN_OPTION) {
        if(check_options(argv[i]) == ERROR_O) {
            perror("Non proper option!\n");
            return -1;
        }
        i++;
    }
    

    file_count = argc - i;
    for( ; i < argc; i++) {
        line_count = line_num = 0;
        start_buffer();

        if((fd = open(argv[i], O_RDONLY)) < 0) {
            perror("Error opening file");
            return -1;
        }

        while((status = get_line(fd)) > 0) {
            int match;

            line_num++;
            match = strcontains(file_reader.buffer, arg_manager.pattern);
            if(match != ((arg_manager.flags & INVERT_MATCH) == INVERT_MATCH)) {
                line_count++;
                if(file_count > 1)
                    printf("%s: ", argv[i]);
                if((arg_manager.flags & LINE_NUMBERS) == LINE_NUMBERS)
                    printf("%d: ", line_num);
                printf("%s", file_reader.buffer);
            }
        }
    
        if((arg_manager.flags & COUNT_MATCHES) == COUNT_MATCHES) {
            if(((arg_manager.flags & INVERT_MATCH) == INVERT_MATCH))
                line_count = line_num - line_count;
            printf("\n%s has [%d] match(es) of \"%s\"\n", argv[i], line_count, arg_manager.pattern);
        }
        
        close(fd);
        free_buffer();
    }

    return 0;
}