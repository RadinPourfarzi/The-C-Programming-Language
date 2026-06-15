/*  ########################################
    ###     Mini Text Search Utility     ###
    ########################################  */

#include <stdio.h>
#include "buffer.h"
#include "search.h"
#include "options.h"

int main(int argc, char *argv[])
{
    int fd, status, i, match;
    unsigned int lc, ln;

    if((status = read_arguments(argc, argv)) < 0) {
        fprintf(stderr, "Error with arguments:\nsearch -options \'Pattern\' Files...\n");
        return -1;
    }
    
    lc = ln = 0;
    if(!(arg_manager.conditions & GIVEN_FILES)) {
        if(start_buffer() < 0) {
            fprintf(stderr, "Error starting buffer\n");
            return -1;
        }
        while(get_line(0) == 1) {
            ln++;
            match = (!(arg_manager.options & IGNORE_CASE)) ? strcontains(file_reader.buffer, arg_manager.pattern) : nocase_strcontains(file_reader.buffer, arg_manager.pattern);
            if(match != ((arg_manager.options & INVERT_MATCH) == INVERT_MATCH)) {
                lc++;
                if((arg_manager.options & LINE_NUMBERS) == LINE_NUMBERS)
                    printf("[%d]: ", ln);
                if(!(arg_manager.options & COUNT_MATCHES))
                    printf("%s", file_reader.buffer);
            }
        }
        if((arg_manager.options & COUNT_MATCHES) == COUNT_MATCHES)
            printf("[%d] matches", lc);
        free_buffer();
    }
    else {
        for(i = arg_manager.first_file; i < argc; i++) {
            lc = ln = 0;
            if((fd = open(argv[i], O_RDONLY)) < 0) {
                fprintf(stderr, "Error opening file \'%s\'\n", argv[i]);
                return -1;
            }
            if(start_buffer() < 0) {
                fprintf(stderr, "Error starting buffer\n");
                return -1;
            }
            while(get_line(fd) == 1) {
                ln++;
                match = (!(arg_manager.options & IGNORE_CASE)) ? strcontains(file_reader.buffer, arg_manager.pattern) : nocase_strcontains(file_reader.buffer, arg_manager.pattern);
                if(match != ((arg_manager.options & INVERT_MATCH) == INVERT_MATCH)) {
                    lc++;
                    if(!(arg_manager.options & COUNT_MATCHES)) {
                        if(arg_manager.file_count > 1)
                            printf("\'%s\':: ", argv[i]);
                        if((arg_manager.options & LINE_NUMBERS) == LINE_NUMBERS)
                            printf("[%d]: ", ln);
                        printf("%s", file_reader.buffer);
                    }
                }
            }
            if((arg_manager.options & COUNT_MATCHES) == COUNT_MATCHES) {
                if(arg_manager.file_count > 1)
                    printf("\'%s\':: ", argv[i]);
                printf("[%d] matches", lc);
            }
            free_buffer();
            close(fd);
        }
    }
    return 0;
}